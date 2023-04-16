#include "Dig.h"

#include "Export_Function.h"

CDig::CDig(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBehavior(pGraphicDev), m_fMagnification(0.f)
{
}

CDig::CDig(const CDig & rhs)
	: CBehavior(rhs), m_fMagnification(rhs.m_fMagnification)
{
}

CDig::~CDig()
{
}

HRESULT CDig::Ready_Behavior()
{
	return S_OK;
}

_int CDig::Update_Component(const _float & fTimeDelta)
{
	CAnimation* pAnimation = dynamic_cast<CAnimation*>(m_pGameObject->Get_Component(L"Animation", ID_ALL));
	if (pAnimation)
		pAnimation->SelectState(ANIM_WALK);

	m_fCurTime += fTimeDelta;

	_float fSpeed = 0.f;
	FAILED_CHECK_RETURN(m_pBlackBoard->Get_Type(L"fSpeed", &fSpeed), BEHAVIOR_FAIL);

	m_pGameObject->m_pTransform->Move_Fly(-fSpeed * m_fMagnification, fTimeDelta);

	if (m_fCurTime - m_fPreTime >= m_fTimer)
	{
		m_fPreTime = m_fCurTime;
		return BEHAVIOR_SUCCES;
	}
	else
		return BEHAVIOR_RUNNING;
}

void CDig::LateUpdate_Component(void)
{
}

void CDig::Render_Component(void)
{
}

CDig * CDig::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CDig* pInstance = new CDig(pGraphicDev);

	if (!pInstance)
		return nullptr;

	return pInstance;
}

CComponent * CDig::Clone(void)
{
	return new CDig(*this);
}

void CDig::Free()
{
	__super::Free();
}
