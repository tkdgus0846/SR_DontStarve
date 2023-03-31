#include "stdafx.h"
#include "Camera.h"

#include "Component.h"

#include "Export_Function.h"


CCamera::CCamera(LPDIRECT3DDEVICE9 pGraphicDev)
	:CComponent(pGraphicDev), m_hWnd(nullptr),
	m_eType(CAM_LAND), m_fLength(0.f)
{
	ZeroMemory(&m_vLook, sizeof(_vec3));
	ZeroMemory(&m_tViewParams, sizeof(VIEWPARAMS));
	ZeroMemory(&m_tProjParams, sizeof(PROJPARAMS));
}

CCamera::CCamera(const CCamera & rhs)
	:CComponent(rhs), m_hWnd(rhs.m_hWnd),
	m_eType(rhs.m_eType), m_fLength(rhs.m_fLength)
{
	m_tViewParams = rhs.m_tViewParams;
	m_tProjParams = rhs.m_tProjParams;
	m_matView = rhs.m_matView;
	m_matProj = rhs.m_matProj;

	m_bFix = true;
}

CCamera::~CCamera()
{
}

HRESULT CCamera::Ready_Camera(VIEWPARAMS& tViewParam, PROJPARAMS& tProjParam, HWND& hWnd)
{
	m_tViewParams = tViewParam;
	m_tProjParams = tProjParam;
	m_hWnd = hWnd;

	m_tViewParams.LookAtLH(&m_matView);
	m_tProjParams.PerspectiveLH(&m_matProj);

	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matProj);

	m_fLength = D3DXVec3Length(&(m_tViewParams.vAt - m_tViewParams.vEye));

	return S_OK;
}

_int CCamera::Update_Component(const _float & fTimeDelta)
{


	m_tViewParams.vEye = m_pGameObject->m_pTransform->m_vInfo[INFO_POS];

	m_tViewParams.vAt = m_tViewParams.vEye + m_pGameObject->m_pTransform->m_vInfo[INFO_LOOK];

	//cout << vLook.x << " " << vLook.y << " " << vLook.z << endl;

	m_tViewParams.LookAtLH(&m_matView);

	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_matView);

	return 0;
}

void CCamera::Key_Input(const _float & fTimeDelta)
{
	_matrix		matCamWorld;
	D3DXMatrixInverse(&matCamWorld, 0, &m_matView);

	if (Engine::Get_DIKeyState(DIK_UP) & 0x80)
	{
		Move_Walk(10.f, fTimeDelta);
	}

	if (Engine::Get_DIKeyState(DIK_DOWN) & 0x80)
	{
		Move_Walk(-10.f, fTimeDelta);
	}

	if (Engine::Get_DIKeyState(DIK_LEFT) & 0x80)
	{
		Move_Strafe(-10.f, fTimeDelta);
	}

	if (Engine::Get_DIKeyState(DIK_RIGHT) & 0x80)
	{
		Move_Strafe(10.f, fTimeDelta);
	}

	if (Engine::Get_DIKeyState(DIK_TAB) & 0x80)
	{
		m_bFix = true;
	}
}

void CCamera::Mouse_Move()
{
	_long dwMouseMove = 0;

	_matrix matCamWorld;
	D3DXMatrixInverse(&matCamWorld, 0, &m_matView);

	if (dwMouseMove = Engine::Get_DIMouseMove(DIMS_Y))
	{
		_vec3 vRight;
		memcpy(&vRight, &matCamWorld.m[0], sizeof(_vec3));

		_matrix matRot;
		D3DXMatrixRotationAxis(&matRot, &vRight, D3DXToRadian(dwMouseMove) / 10.f);

		_vec3 vLook = m_tViewParams.vAt - m_tViewParams.vEye;
		D3DXVec3TransformNormal(&vLook, &vLook, &matRot);

		m_tViewParams.vAt = m_tViewParams.vEye + vLook;
	}

	if (dwMouseMove = Engine::Get_DIMouseMove(DIMS_X))
	{
		
		_matrix matRot;
		_vec3 vUp = { 0.f, 1.f, 0.f };

		D3DXMatrixRotationAxis(&matRot, &vUp, D3DXToRadian(dwMouseMove / 10.f));

		_vec3 vLook = m_tViewParams.vAt - m_tViewParams.vEye;
		D3DXVec3TransformNormal(&vLook, &vLook, &matRot);
		
		m_tViewParams.vAt = m_tViewParams.vEye + vLook;
	}
}

void CCamera::Fix_Mouse()
{
	POINT ptMouse{ WINCX >> 1, WINCY >> 1 };

	ClientToScreen(m_hWnd, &ptMouse);
	SetCursorPos(ptMouse.x, ptMouse.y);
}

void CCamera::Move_Strafe(const _float & fUnits, const _float& fTimeDelta)
{
	_vec3 vUp, vLook, vRight;

	switch (m_eType)
	{
	case Engine::CCamera::CAM_LAND:
		vUp = m_pGameObject->m_pTransform->m_vInfo[INFO_UP];
		vLook = m_pGameObject->m_pTransform->m_vInfo[INFO_LOOK];

		D3DXVec3Cross(&vRight, &vUp, &vLook);
		D3DXVec3Normalize(&vRight, &vRight);

		m_tViewParams.vEye += _vec3(vRight.x, 0.f, vRight.z) * fUnits * fTimeDelta;
		m_tViewParams.vAt += _vec3(vRight.x, 0.f, vRight.z) * fUnits * fTimeDelta;
		break;

	case Engine::CCamera::CAM_FLY:
		vLook = m_tViewParams.vAt - m_tViewParams.vEye;

		D3DXVec3Cross(&vRight, &_vec3{ 0.f, 1.f, 0.f }, &vLook);
		D3DXVec3Normalize(&vRight, &vRight);

		m_tViewParams.vEye += vRight * fUnits * fTimeDelta;
		m_tViewParams.vAt += vRight * fUnits * fTimeDelta;
		break;
	}
}

void CCamera::Move_Fly(const _float & fUnits, const _float& fTimeDelta)
{
	_vec3 vUp, vLook, vRight;

	switch (m_eType)
	{
	case Engine::CCamera::CAM_LAND:
		return;

	case Engine::CCamera::CAM_FLY:
		vLook = m_tViewParams.vAt - m_tViewParams.vEye;

		D3DXVec3Cross(&vRight, &_vec3{ 0.f, 1.f, 0.f }, &vLook);
		D3DXVec3Cross(&vUp, &vLook, &vRight);
		D3DXVec3Normalize(&vUp, &vUp);

		m_tViewParams.vEye += vUp * fUnits * fTimeDelta;
		m_tViewParams.vAt += vUp * fUnits * fTimeDelta;
		break;
	}
}

void CCamera::Move_Walk(const _float & fUnits, const _float& fTimeDelta)
{
	_vec3 vLook;

	switch (m_eType)
	{
	case Engine::CCamera::CAM_LAND:
		vLook = m_pGameObject->m_pTransform->m_vInfo[INFO_LOOK];;

		D3DXVec3Normalize(&vLook, &vLook);

		m_tViewParams.vEye += _vec3(vLook.x, 0.f, vLook.z) * fUnits * fTimeDelta;
		m_tViewParams.vAt += _vec3(vLook.x, 0.f, vLook.z) * fUnits * fTimeDelta;
		break;

	case Engine::CCamera::CAM_FLY:
		vLook = m_tViewParams.vAt - m_tViewParams.vEye;

		D3DXVec3Normalize(&vLook, &vLook);

		m_tViewParams.vEye += vLook * fUnits * fTimeDelta;
		m_tViewParams.vAt += vLook * fUnits * fTimeDelta;
		break;
	}
}

//void CCamera::Rot_Pitch(const _float & fAngle, const _float& fTimeDelta)
//{
//	if (0 == fAngle)
//		return;
//
//	_matrix matRot;
//
//	switch (m_eType)
//	{
//	case Engine::CCamera::CAM_LAND:
//
//	case Engine::CCamera::CAM_FLY:
//		D3DXMatrixRotationAxis(&matRot, &m_vInfo[INFO_RIGHT], D3DXToRadian(fAngle) * fTimeDelta);
//
//		D3DXVec3TransformCoord(&m_vInfo[INFO_UP], &m_vInfo[INFO_UP], &matRot);
//		D3DXVec3TransformCoord(&m_vInfo[INFO_LOOK], &m_vInfo[INFO_LOOK], &matRot);
//		break;
//	}
//}
//
//void CCamera::Rot_Yaw(const _float & fAngle, const _float& fTimeDelta)
//{
//	if (0 == fAngle)
//		return;
//
//	_matrix matRot;
//
//	switch (m_eType)
//	{
//	case Engine::CCamera::CAM_LAND:
//		D3DXMatrixRotationAxis(&matRot, &_vec3(0.f, 1.f, 0.f), D3DXToRadian(fAngle) * fTimeDelta);
//		break;
//
//	case Engine::CCamera::CAM_FLY:
//		D3DXMatrixRotationAxis(&matRot, &m_vInfo[INFO_UP], D3DXToRadian(fAngle) * fTimeDelta);
//		break;
//	}
//
//	D3DXVec3TransformCoord(&m_vInfo[INFO_RIGHT], &m_vInfo[INFO_RIGHT], &matRot);
//	D3DXVec3TransformCoord(&m_vInfo[INFO_LOOK], &m_vInfo[INFO_LOOK], &matRot);
//}
//
//void CCamera::Rot_Roll(const _float & fAngle, const _float& fTimeDelta)
//{
//	if (0 == fAngle)
//		return;
//
//	_matrix matRot;
//
//	switch (m_eType)
//	{
//	case Engine::CCamera::CAM_LAND:
//		return;
//
//	case Engine::CCamera::CAM_FLY:
//		D3DXMatrixRotationAxis(&matRot, &m_vInfo[INFO_LOOK], D3DXToRadian(fAngle) * fTimeDelta);
//		D3DXVec3TransformCoord(&m_vInfo[INFO_UP], &m_vInfo[INFO_UP], &matRot);
//		D3DXVec3TransformCoord(&m_vInfo[INFO_LOOK], &m_vInfo[INFO_LOOK], &matRot);
//		break;
//	}
//}
CCamera * CCamera::Create(LPDIRECT3DDEVICE9 pGraphicDev, VIEWPARAMS& tViewParam, PROJPARAMS& tProjParam, HWND hWnd)
{
	CCamera* pInstance = new CCamera(pGraphicDev);

	if (FAILED(pInstance->Ready_Camera(tViewParam, tProjParam, hWnd)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CCamera::Clone(void)
{
	return new CCamera(*this);
}

void CCamera::Free()
{
	__super::Free();
}
