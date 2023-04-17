#include "MoveUp.h"

#include "Export_Function.h"

CMoveUp::CMoveUp(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBehavior(pGraphicDev)
{
}

CMoveUp::CMoveUp(const CMoveUp & rhs)
	: CBehavior(rhs)
{
}

CMoveUp::~CMoveUp()
{
}

HRESULT CMoveUp::Ready_Behavior()
{
	return S_OK;
}

_int CMoveUp::Update_Component(const _float & fTimeDelta)
{
	CAnimation* pAnimation = dynamic_cast<CAnimation*>(m_pGameObject->Get_Component(L"Animation", ID_ALL));
	if (pAnimation)
		pAnimation->SelectState(ANIM_WALK);

	m_fCurTime += fTimeDelta;

	_float fSpeed = 0.f;
	FAILED_CHECK_RETURN(m_pBlackBoard->Get_Type(L"fSpeed", fSpeed), BEHAVIOR_FAIL);

	m_pGameObject->m_pTransform->Move_Fly(fSpeed * m_fMagnification, fTimeDelta);

	if (m_fCurTime - m_fPreTime >= m_fTimer)
	{
		m_fPreTime = m_fCurTime;
		return BEHAVIOR_SUCCES;
	}
	else
		return BEHAVIOR_RUNNING;
}

void CMoveUp::LateUpdate_Component(void)
{
}

void CMoveUp::Render_Component(void)
{
}

CMoveUp * CMoveUp::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMoveUp* pInstance = new CMoveUp(pGraphicDev);

	if (FAILED(pInstance->Ready_Behavior()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CMoveUp::Clone(void)
{
	return new CMoveUp(*this);
}

void CMoveUp::Free()
{
	__super::Free();
}
