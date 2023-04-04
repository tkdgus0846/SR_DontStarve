#include "stdafx.h"
#include "RotToFace.h"

#include "Export_Function.h"

CRotToFace::CRotToFace(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBehavior(pGraphicDev)
{
}

CRotToFace::CRotToFace(const CRotToFace & rhs)
	:CBehavior(rhs)
{
}

CRotToFace::~CRotToFace()
{
}

HRESULT CRotToFace::Ready_Behavior()
{
	return S_OK;
}

_int CRotToFace::Update_Component(const _float & fTimeDelta)
{
	// 임시코드
	if (GetAsyncKeyState(VK_SPACE))
		return BEHAVIOR_FALSE;
	//
	CTransform* pTargetTransform = dynamic_cast<CTransform*>(Engine::Get_Component(LAYER_PLAYER, L"Player", L"Transform", ID_DYNAMIC));

	_float fSpeed = 0.f;
	FAILED_CHECK_RETURN(m_pBlackBoard->Get_Type(L"fSpeed", &fSpeed), BEHAVIOR_FALSE);

	_vec3 vLook = m_pGameObject->m_pTransform->m_vInfo[INFO_LOOK];
	_vec3 vLookToTarget = pTargetTransform->m_vInfo[INFO_POS] - m_pGameObject->m_pTransform->m_vInfo[INFO_POS];

	vLook.Normalize();
	vLookToTarget.Normalize();

	_float fAngle = vLook.Degree(vLookToTarget);
	_vec3 vDir = vLookToTarget - vLook;
	_vec3 vAxis = vLook.Cross(vDir);

	_matrix matRot;

	D3DXMatrixRotationAxis(&matRot, &vAxis, D3DXToRadian(fAngle) * fTimeDelta * 2.f);
	D3DXVec3TransformCoord(&m_pGameObject->m_pTransform->m_vInfo[INFO_LOOK], 
		&m_pGameObject->m_pTransform->m_vInfo[INFO_LOOK], &matRot);

	m_pGameObject->m_pTransform->Set_Target(pTargetTransform->m_vInfo[INFO_POS]);

	return BEHAVIOR_TRUE;
}

void CRotToFace::LateUpdate_Component(void)
{
	__super::LateUpdate_Component();
}

void CRotToFace::Render_Component(void)
{
	__super::Render_Component();
}

CRotToFace * CRotToFace::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRotToFace* pInstance = new CRotToFace(pGraphicDev);

	if (!pInstance)
		return nullptr;

	return pInstance;
}

CComponent * CRotToFace::Clone(void)
{
	return new CRotToFace(*this);
}

void CRotToFace::Free()
{
	__super::Free();
}
