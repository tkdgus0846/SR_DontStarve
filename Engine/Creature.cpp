#include "stdafx.h"
#include "Creature.h"


CCreature::CCreature(LPDIRECT3DDEVICE9 pGrapicDev)
	: CGameObject(pGrapicDev), m_fSpeed(0.f)
	, m_iHp(0), m_iAttack(0)
{
}

CCreature::~CCreature()
{
}

HRESULT CCreature::Ready_GameObject(void)
{
	__super::Ready_GameObject();

	return S_OK;
}

_int CCreature::Update_GameObject(const _float & fTimeDelta)
{
	__super::Update_GameObject(fTimeDelta);

	return 0;
}

void CCreature::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CCreature::Render_GameObject(void)
{
	__super::Render_GameObject();
}

HRESULT CCreature::Add_Component()
{
	return S_OK;
}

void CCreature::Free()
{
	__super::Free();
}
