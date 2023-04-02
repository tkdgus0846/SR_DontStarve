#include "stdafx.h"
#include "Wait.h"


CWait::CWait(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBehavior(pGraphicDev), m_fTime(0.f)
	, m_fLimit(0.f)
{
}

CWait::CWait(const CWait & rhs)
	: CBehavior(rhs), m_fTime(rhs.m_fTime)
	, m_fLimit(rhs.m_fLimit)
{
}

CWait::~CWait()
{
}


HRESULT CWait::Ready_Behavior()
{
	__super::Ready_Composite();
	return S_OK;
}

_int CWait::Update_Component(const _float & fTimeDelta)
{
	m_fTime += fTimeDelta;

	if (m_fTime >= m_fLimit)
		return BEHAVIOR_FALSE;

	return RUNNING;
}

CWait * CWait::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CWait* pInstance = new CWait(pGraphicDev);

	if (FAILED(pInstance->Ready_Behavior()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CWait::Clone(void)
{
	return new CWait(*this);
}

void CWait::Free()
{
	__super::Free();
}
