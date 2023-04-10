#include "stdafx.h"
#include "RotToFace.h"

#include "Export_Utility.h"

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
	CTransform* pTargetTransform = dynamic_cast<CTransform*>(Engine::Get_Component(LAYER_PLAYER, L"Player", L"Transform", ID_UPDATE));

	m_pGameObject->m_pTransform->Rot_To_TargetPos(pTargetTransform->m_vInfo[INFO_POS], fTimeDelta);

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

	if (FAILED(pInstance->Ready_Behavior()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

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
