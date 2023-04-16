#include "CoolTime.h"

#include "Export_Function.h"

CCoolTime::CCoolTime(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBehavior(pGraphicDev)
{
}

CCoolTime::CCoolTime(const CCoolTime & rhs)
	: CBehavior(rhs)
{
}

CCoolTime::~CCoolTime()
{
}

HRESULT CCoolTime::Ready_Behavior()
{
	return S_OK;
}

_int CCoolTime::Update_Component(const _float & fTimeDelta)
{
	m_fCurTime = Get_WorldTime();

	if (m_fCurTime - m_fPreTime > m_fTimer)
	{
		m_fPreTime = m_fCurTime;
		return BEHAVIOR_SUCCES;
	}

	return BEHAVIOR_FAIL;
}

CCoolTime * CCoolTime::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCoolTime* pInstance = new CCoolTime(pGraphicDev);

	if (FAILED(pInstance->Ready_Behavior()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CCoolTime::Clone(void)
{
	return new CCoolTime(*this);
}

void CCoolTime::Free()
{
	__super::Free();
}
