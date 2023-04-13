#include "TimeInLimit.h"

#include "Export_Function.h"

CTimeInLimit::CTimeInLimit(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBehavior(pGraphicDev)
{
}

CTimeInLimit::CTimeInLimit(const CTimeInLimit & rhs)
	: CBehavior(rhs)
{
}

CTimeInLimit::~CTimeInLimit()
{
}

HRESULT CTimeInLimit::Ready_Behavior()
{
	return S_OK;
}

_int CTimeInLimit::Update_Component(const _float & fTimeDelta)
{
	m_fCurTime = Get_WorldTime();

	if (m_fCurTime - m_fPreTime > m_fTimer)
	{
		m_fPreTime = m_fCurTime;
		return BEHAVIOR_FAIL;
	}

	return BEHAVIOR_SUCCES;
}

void CTimeInLimit::LateUpdate_Component(void)
{
	__super::LateUpdate_Component();
}

void CTimeInLimit::Render_Component(void)
{
}

CTimeInLimit * CTimeInLimit::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTimeInLimit* pInstance = new CTimeInLimit(pGraphicDev);

	if (FAILED(pInstance->Ready_Behavior()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CTimeInLimit::Clone(void)
{
	return new CTimeInLimit(*this);
}

void CTimeInLimit::Free()
{
	__super::Free();
}
