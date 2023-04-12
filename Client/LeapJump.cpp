#include "LeapJump.h"

#include "Export_Function.h"

CLeapJump::CLeapJump(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBehavior(pGraphicDev), m_fTime(0.f),
	m_fInit(0.f)
{
}

CLeapJump::CLeapJump(const CLeapJump & rhs)
	: CBehavior(rhs), m_fTime(rhs.m_fTime),
	m_fInit(rhs.m_fInit)
{
}

CLeapJump::~CLeapJump()
{
}

HRESULT CLeapJump::Ready_Behavior()
{
	m_fInit = m_pGameObject->m_pTransform->m_vInfo[INFO_POS].y;

	return S_OK;
}

_int CLeapJump::Update_Component(const _float & fTimeDelta)
{
	m_fCurTime = Get_WorldTime();

	if (m_fInit > m_pGameObject->m_pTransform->m_vInfo[INFO_POS].y)
	{
		m_pGameObject->m_pTransform->m_vInfo[INFO_POS].y = m_fInit;
		m_fPreTime = m_fCurTime;
		m_fTime = 0.f;

		return BEHAVIOR_SUCCES;
	}

	_float fSpeed = 0.f;
	FAILED_CHECK_RETURN(m_pBlackBoard->Get_Type(L"fSpeed", &fSpeed), BEHAVIOR_FAIL);
	
	if (m_fCurTime - m_fPreTime >= m_fTime)
	{
		m_pGameObject->m_pTransform->Move_Walk(fSpeed, fTimeDelta);

		m_fTime += fTimeDelta * 7.f;

		_float fY = fSpeed * m_fTime - 4.9f * m_fTime * m_fTime;

		m_pGameObject->m_pTransform->m_vInfo[INFO_POS].y += fY / 8.f;
	}

	return BEHAVIOR_RUNNING;
}

void CLeapJump::Render_Component(void)
{
	__super::Render_Component();
}

CLeapJump * CLeapJump::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLeapJump* pInstance = new CLeapJump(pGraphicDev);

	if (!pInstance)
		return nullptr;

	return pInstance;
}

CComponent * CLeapJump::Clone(void)
{
	return new CLeapJump(*this);
}

void CLeapJump::Free()
{
	__super::Free();
}
