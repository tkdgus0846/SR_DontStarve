#include "stdafx.h"
#include "MoveLook.h"

#include "Export_Utility.h"

CMoveLook::CMoveLook(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBehavior(pGraphicDev)
	, m_fTimer(0.f), m_fLimit(0.f)
{
}

CMoveLook::CMoveLook(const CMoveLook & rhs)
	: CBehavior(rhs), m_fTimer(rhs.m_fTimer)
	, m_fLimit(rhs.m_fLimit)
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
	m_fTimer += fTimeDelta;

	_float fSpeed = 0.f;
	FAILED_CHECK_RETURN(m_pBlackBoard->Get_Type(L"fSpeed", &fSpeed), BEHAVIOR_FALSE);

	m_pGameObject->m_pTransform->Move_Walk(fSpeed, fTimeDelta);

	if (m_fTimer >= m_fLimit)
	{
		m_fTimer = 0.f;
		return BEHAVIOR_TRUE;
	}
	else
		return RUNNING;
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
