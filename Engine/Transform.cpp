#include "stdafx.h"
#include "Transform.h"

CTransform::CTransform(LPDIRECT3DDEVICE9 pGraphicDev)
	: CComponent(pGraphicDev)
	, m_vScale(1.f, 1.f, 1.f)
	, m_eMoveType(LANDOBJECT)
{
	ZeroMemory(&m_vInfo, sizeof(m_vInfo));
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matBill);
}

CTransform::CTransform(const CTransform & rhs)
	: CComponent(rhs)
	, m_vScale(rhs.m_vScale)
	, m_matWorld(rhs.m_matWorld)
	, m_matBill(rhs.m_matBill)
	, m_eMoveType(rhs.m_eMoveType)
{
	m_RenderOrder = 0;
	for (size_t i = 0; i < INFO_END; ++i)
		m_vInfo[i] = rhs.m_vInfo[i];
}

CTransform::~CTransform()
{
}

void Engine::CTransform::Set_Dir(const _vec3& dir)
{
	_vec3 vDir = dir;
	_vec3 vUp, vRight;

	vUp = { 0.f, 1.f, 0.f };
	vDir.Normalize();

	vRight = vUp.Cross(vDir);
	vUp = vDir.Cross(vRight);

	m_vInfo[INFO_LOOK] = vDir;
	m_vInfo[INFO_RIGHT] = vRight;
	m_vInfo[INFO_UP] = vUp;
}

void Engine::CTransform::Set_Target(const _vec3& targetPos)
{
	_vec3 vDir = targetPos - m_vInfo[INFO_POS];
	_vec3 vUp, vRight;

	vUp = { 0.f, 1.f, 0.f };
	vDir.Normalize();

	vRight = vUp.Cross(vDir);
	vUp = vDir.Cross(vRight);

	m_vInfo[INFO_LOOK] = vDir;
	m_vInfo[INFO_RIGHT] = vRight;
	m_vInfo[INFO_UP] = vUp;
}

void CTransform::Rot_To_TargetPos(const _vec3 & vTargetPos, const _float& fTimeDelta)
{
	_vec3 vLook = m_vInfo[INFO_LOOK];
	_vec3 vLookToTarget = vTargetPos - m_vInfo[INFO_POS];

	vLook.Normalize();
	vLookToTarget.Normalize();

	_float fAngle = vLook.Degree(vLookToTarget);
	_vec3 vDir = vLookToTarget - vLook;
	_vec3 vAxis = vLook.Cross(vDir);

	_matrix matRot;

	D3DXMatrixRotationAxis(&matRot, &vAxis, D3DXToRadian(fAngle) * fTimeDelta * 2.f);
	D3DXVec3TransformCoord(&m_vInfo[INFO_LOOK],
		&m_vInfo[INFO_LOOK], &matRot);
}

void CTransform::Move_Strafe(const _float & fUnits, const _float& fTimeDelta)
{
	_vec3 vDir;

	switch (m_eMoveType)
	{
	case Engine::CTransform::LANDOBJECT:
		D3DXVec3Cross(&vDir, &m_vInfo[INFO_UP], &m_vInfo[INFO_LOOK]);
		m_vInfo[INFO_POS] += _vec3(vDir.x, 0.f, vDir.z) * fUnits * fTimeDelta;
		break;

	case Engine::CTransform::AIRCRAFT:
		m_vInfo[INFO_POS] += m_vInfo[INFO_RIGHT] * fUnits * fTimeDelta;
		break;
	}
}

void CTransform::Move_Fly(const _float & fUnits, const _float& fTimeDelta)
{
	switch (m_eMoveType)
	{
	case Engine::CTransform::LANDOBJECT:
		return;

	case Engine::CTransform::AIRCRAFT:
		m_vInfo[INFO_POS] += m_vInfo[INFO_UP] * fUnits * fTimeDelta;
		break;
	}
}

void CTransform::Move_Walk(const _float & fUnits, const _float& fTimeDelta)
{
	_vec3 vDir;

	switch (m_eMoveType)
	{
	case Engine::CTransform::LANDOBJECT:
		D3DXVec3Cross(&vDir, &m_vInfo[INFO_RIGHT], &m_vInfo[INFO_UP]);
		m_vInfo[INFO_POS] += _vec3(vDir.x, 0.f, vDir.z) * fUnits * fTimeDelta;
		break;

	case Engine::CTransform::AIRCRAFT:
		m_vInfo[INFO_POS] += m_vInfo[INFO_LOOK] * fUnits * fTimeDelta;
		break;
	}
}

void CTransform::Rot_Pitch(const _float & fAngle, const _float& fTimeDelta)
{
	if (0 == fAngle)
		return;

	_matrix matRot;

	switch (m_eMoveType)
	{
	case Engine::CTransform::LANDOBJECT:

	case Engine::CTransform::AIRCRAFT:
		D3DXMatrixRotationAxis(&matRot, &m_vInfo[INFO_RIGHT], D3DXToRadian(fAngle) * fTimeDelta);

		D3DXVec3TransformCoord(&m_vInfo[INFO_UP], &m_vInfo[INFO_UP], &matRot);
		D3DXVec3TransformCoord(&m_vInfo[INFO_LOOK], &m_vInfo[INFO_LOOK], &matRot);
		break;
	}
}

void CTransform::Rot_Yaw(const _float & fAngle, const _float& fTimeDelta)
{
	if (0 == fAngle)
		return;

	_matrix matRot;

	switch (m_eMoveType)
	{
	case Engine::CTransform::LANDOBJECT:
		D3DXMatrixRotationAxis(&matRot, &_vec3(0.f, 1.f, 0.f), D3DXToRadian(fAngle) * fTimeDelta);
		break;

	case Engine::CTransform::AIRCRAFT:
		D3DXMatrixRotationAxis(&matRot, &m_vInfo[INFO_UP], D3DXToRadian(fAngle) * fTimeDelta);
		break;
	}

	D3DXVec3TransformCoord(&m_vInfo[INFO_RIGHT], &m_vInfo[INFO_RIGHT], &matRot);
	D3DXVec3TransformCoord(&m_vInfo[INFO_LOOK], &m_vInfo[INFO_LOOK], &matRot);
}

void CTransform::Rot_Roll(const _float & fAngle, const _float& fTimeDelta)
{
	if (0 == fAngle)
		return;

	_matrix matRot;

	switch (m_eMoveType)
	{
	case Engine::CTransform::LANDOBJECT:
		return;

	case Engine::CTransform::AIRCRAFT:
		D3DXMatrixRotationAxis(&matRot, &m_vInfo[INFO_LOOK], D3DXToRadian(fAngle) * fTimeDelta);
		D3DXVec3TransformCoord(&m_vInfo[INFO_UP], &m_vInfo[INFO_UP], &matRot);
		D3DXVec3TransformCoord(&m_vInfo[INFO_LOOK], &m_vInfo[INFO_LOOK], &matRot);
		break;
	}
}

void Engine::CTransform::Chase_Target(const _vec3* pTargetPos, const _float& fSpeed, const _float& fTimeDelta)
{
	_vec3	vDir = *pTargetPos - m_vInfo[INFO_POS];

	m_vInfo[INFO_POS] += *D3DXVec3Normalize(&vDir, &vDir) * fSpeed * fTimeDelta;

	_matrix		matRot, matTrans;

	matRot = *Compute_Lookattarget(pTargetPos);

	D3DXMatrixTranslation(&matTrans,
		m_vInfo[INFO_POS].x,
		m_vInfo[INFO_POS].y,
		m_vInfo[INFO_POS].z);

	m_matWorld = matRot * matTrans;

}

_bool CTransform::WriteTransformFile(HANDLE hFile, DWORD& dwByte)
{
	WriteFile(hFile, &m_eMoveType, sizeof(MOVETYPE), &dwByte, nullptr);
	for (_int i = 0; i < INFO_END; ++i)
		WriteFile(hFile, &m_vInfo[i], sizeof(_vec3), &dwByte, nullptr);
	WriteFile(hFile, &m_vScale, sizeof(_vec3), &dwByte, nullptr);

	return true;
}

_bool	CTransform::ReadTransformFile(HANDLE hFile, DWORD& dwByte)
{
	ReadFile(hFile, &m_eMoveType, sizeof(MOVETYPE), &dwByte, nullptr);
	for (_int i = 0; i < INFO_END; ++i)
		ReadFile(hFile, &m_vInfo[i], sizeof(_vec3), &dwByte, nullptr);
	ReadFile(hFile, &m_vScale, sizeof(_vec3), &dwByte, nullptr);

	return true;
}

_matrix* Engine::CTransform::Compute_Lookattarget(const _vec3* pTargetPos)
{
	_vec3	vDir = *pTargetPos - m_vInfo[INFO_POS];

	_matrix	matRot;
	_vec3	vAxis, vUp;

	return reinterpret_cast<_matrix*>(D3DXMatrixRotationAxis(&matRot, 
								  D3DXVec3Cross(&vAxis, &m_vInfo[INFO_UP], &vDir),
								  acosf(D3DXVec3Dot(D3DXVec3Normalize(&vDir, &vDir), 
												    D3DXVec3Normalize(&vUp, &m_vInfo[INFO_UP])))));
}

HRESULT CTransform::Ready_Transform(void)
{
	D3DXMatrixIdentity(&m_matWorld);

	for (size_t i = 0; i < INFO_END; ++i)
		memcpy(&m_vInfo[i], &m_matWorld.m[i][0], sizeof(_vec3));

	return S_OK;
}

_int CTransform::Update_Component(const _float & fTimeDelta)
{
	D3DXMatrixIdentity(&m_matWorld);

	/*for (size_t i = 0; i < INFO_POS; ++i)
		memcpy(&m_vInfo[i], &m_matWorld.m[i][0], sizeof(_vec3));*/

	// ũ�� ��ȯ
	_matrix matScale;
	D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);

	// ȸ�� ��ȯ
	_vec3 vRight, vUp, vLook;

	_matrix	matRotation;
	D3DXMatrixIdentity(&matRotation);

	D3DXVec3Normalize(&vRight, &m_vInfo[INFO_RIGHT]);
	D3DXVec3Normalize(&vUp, &m_vInfo[INFO_UP]);
	D3DXVec3Normalize(&vLook, &m_vInfo[INFO_LOOK]);

	matRotation._11 = vRight.x; matRotation._12 = vRight.y; matRotation._13 = vRight.z;
	matRotation._21 = vUp.x;	matRotation._22 = vUp.y;	matRotation._23 = vUp.z;
	matRotation._31 = vLook.x;	matRotation._32 = vLook.y;	matRotation._33 = vLook.z;

	// ��ġ ��ȯ
	_matrix			matTrans;
	D3DXMatrixTranslation(&matTrans, m_vInfo[INFO_POS].x, m_vInfo[INFO_POS].y, m_vInfo[INFO_POS].z);

	// �ʱ�ȭ���� �׵�����̰� ��� SetBillBoard�� �θ��� ���� �����
	m_matWorld = matScale * m_matBill * matRotation * matTrans;

	return 0;
}

void CTransform::LateUpdate_Component(void)
{
}

CTransform * CTransform::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTransform *	pInstance = new CTransform(pGraphicDev);

	if (FAILED(pInstance->Ready_Transform()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CTransform::Clone(void)
{
	return new CTransform(*this);
}

void CTransform::Free(void)
{
	__super::Free();
}
