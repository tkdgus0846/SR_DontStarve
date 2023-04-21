#include "BigJump.h"

#include "Export_Function.h"

CBigJump::CBigJump(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBehavior(pGraphicDev), m_bStop(false)
{
}

CBigJump::CBigJump(const CBigJump & rhs)
	: CBehavior(rhs), m_bStop(rhs.m_bStop)
{
}

CBigJump::~CBigJump()
{
}

HRESULT CBigJump::Ready_Behavior()
{
	m_fInit = m_pGameObject->m_pTransform->m_vScale.y;
	m_fCurTime = 0.f;
	m_fPreTime = 0.f;
	return S_OK;
}

_int CBigJump::Update_Component(const _float & fTimeDelta)
{
	static _bool bJump = true;
	CAnimation* pAnimation = dynamic_cast<CAnimation*>(m_pGameObject->Get_Component(L"Animation", ID_ALL));
	if (pAnimation)
		pAnimation->SelectState(ANIM_JUMP);

	_float fSpeed = 0.f;
	m_pBlackBoard->Get_Type(L"fSpeed", fSpeed);

	if(bJump)
		m_fTime += fTimeDelta * 7.f;
	
	_float fY = m_fForce * m_fTime - 4.9f * m_fTime * m_fTime;

	if (fY < 0 && m_bStop)
	{
		m_pGameObject->m_pTransform->m_vInfo[INFO_POS].y = 220.f;
		m_pGameObject->m_pTransform->Set_MoveType(CTransform::AIRCRAFT);
		m_fCurTime = Get_WorldTime();

		if (bJump)
		{
			bJump = false;
			return BEHAVIOR_SUCCES;
		}

		if (m_fCurTime - m_fPreTime >= m_fTimer)
		{
			bJump = true;
			m_bStop = false;
		}
	}
	else
		m_fPreTime = Get_WorldTime();

	if(bJump)
		m_pGameObject->m_pTransform->m_vInfo[INFO_POS].y += fY / 8.f;

	if (m_fInit > m_pGameObject->m_pTransform->m_vInfo[INFO_POS].y)
	{
		m_pGameObject->m_pTransform->Set_MoveType(CTransform::LANDOBJECT);
		m_pGameObject->m_pTransform->m_vInfo[INFO_POS].y = m_fInit;
		m_fPreTime = m_fCurTime;
		m_fTime = 0.f;
		m_bStop = m_bSetStop;
		Shake_Camera(SHAKE_Y, 3.f, 6.f);
		return BEHAVIOR_SUCCES;
	}

	return BEHAVIOR_RUNNING;
}

void CBigJump::Render_Component(void)
{
	__super::Render_Component();
}

CBigJump * CBigJump::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBigJump* pInstance = new CBigJump(pGraphicDev);

	if (!pInstance)
		return nullptr;

	return pInstance;
}

CComponent * CBigJump::Clone(void)
{
	return new CBigJump(*this);
}

void CBigJump::Free()
{
	__super::Free();
}
