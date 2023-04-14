#include "stdafx.h"
#include "Attack.h"

#include "Export_Function.h"
#include "BulletMgr.h"
#include "NormalBullet.h"

CAttack::CAttack(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBehavior(pGraphicDev)
{
}

CAttack::CAttack(const CAttack & rhs)
	: CBehavior(rhs)
{
}

CAttack::~CAttack()
{
}

HRESULT CAttack::Ready_Behavior()
{
	return S_OK;
}

_int CAttack::Update_Component(const _float & fTimeDelta)
{
	m_fCurTime = Get_WorldTime();

	if (m_fCurTime - m_fPreTime > m_fTimer)
	{
		CBullet* bullet = CBulletMgr::GetInstance()->Pop(
			L"NormalBullet", m_pGraphicDev, 
			m_pGameObject->m_pTransform->m_vInfo[INFO_POS], 
			m_pGameObject->m_pTransform->m_vInfo[INFO_LOOK], { 1.f,1.f,1.f }, true);

		m_fPreTime = m_fCurTime;
		Add_GameObject(bullet);
	}

	return BEHAVIOR_SUCCES;
}

void CAttack::Render_Component(void)
{
	__super::Render_Component();
}

CAttack * CAttack::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CAttack* pInstance = new CAttack(pGraphicDev);

	if (!pInstance)
		return nullptr;

	return pInstance;
}

CComponent * CAttack::Clone(void)
{
	return new CAttack(*this);
}

void CAttack::Free()
{
	__super::Free();
}
