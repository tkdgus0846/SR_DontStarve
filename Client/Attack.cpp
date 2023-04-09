#include "stdafx.h"
#include "Attack.h"

#include "Export_Function.h"
#include "BulletMgr.h"
#include "NormalBullet.h"

CAttack::CAttack(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBehavior(pGraphicDev), m_fCoolTime(0.f)
{
}

CAttack::CAttack(const CAttack & rhs)
	: CBehavior(rhs), m_fCoolTime(rhs.m_fCoolTime)
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
	m_fCoolTime += fTimeDelta;

	if (m_fCoolTime > 0.5f)
	{
		CNormalBullet* bullet = CBulletMgr::GetInstance()->Pop<CNormalBullet>(
			L"NormalBullet", m_pGraphicDev, 
			m_pGameObject->m_pTransform->m_vInfo[INFO_POS], 
			m_pGameObject->m_pTransform->m_vInfo[INFO_LOOK], { 1.f,1.f,1.f }, true);
		Add_GameObject(LAYER_BULLET, L"Bullet", bullet);
		m_fCoolTime = 0.f;
	}

	return BEHAVIOR_TRUE;
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
