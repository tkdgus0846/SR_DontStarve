#include "stdafx.h"
#include "Wait.h"

#include "Export_Utility.h"

CWait::CWait(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBehavior(pGraphicDev)
{
}

CWait::CWait(const CWait & rhs)
	: CBehavior(rhs)
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
	m_fCurTime += fTimeDelta;

	if (m_fCurTime - m_fPreTime >= m_fTimer)
	{
		m_fPreTime = m_fCurTime;
		return BEHAVIOR_SUCCES;
	}

	return BEHAVIOR_RUNNING;
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
