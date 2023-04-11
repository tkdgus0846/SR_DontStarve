#include "stdafx.h"
#include "MoveLook.h"

#include "Export_Utility.h"

CMoveLook::CMoveLook(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBehavior(pGraphicDev)
{
}

CMoveLook::CMoveLook(const CMoveLook & rhs)
	: CBehavior(rhs)
{
}

CMoveLook::~CMoveLook()
{
}

HRESULT CMoveLook::Ready_Behavior()
{
	__super::Ready_Composite();

	return S_OK;
}

_int CMoveLook::Update_Component(const _float & fTimeDelta)
{
	m_fCurTime += fTimeDelta;

	_float fSpeed = 0.f;
	FAILED_CHECK_RETURN(m_pBlackBoard->Get_Type(L"fSpeed", &fSpeed), BEHAVIOR_FAIL);

	m_pGameObject->m_pTransform->Move_Walk(fSpeed, fTimeDelta);

	if (m_fCurTime - m_fPreTime >= m_fTime)
	{
		m_fPreTime = m_fCurTime;
		return BEHAVIOR_SUCCES;
	}
	else
		return BEHAVIOR_RUNNING;
}

void CMoveLook::Render_Component(void)
{
	__super::Render_Component();
}

CComponent * CMoveLook::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMoveLook* pInstance = new CMoveLook(pGraphicDev);
	
	if (FAILED(pInstance->Ready_Behavior()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CMoveLook::Clone(void)
{
	return new CMoveLook(*this);
}

void CMoveLook::Free()
{
	__super::Free();
}
