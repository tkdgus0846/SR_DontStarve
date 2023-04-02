#include "stdafx.h"
#include "Bullet.h"

#include "Export_Function.h"

CBullet::CBullet(LPDIRECT3DDEVICE9 pGraphicDev) :
	CGameObject(pGraphicDev)
{
	CComponent* pComponent = Engine::Clone_Proto(L"Collider", this);
	m_uMapComponent[ID_DYNAMIC].insert({ L"Collider", pComponent });
}

CBullet::~CBullet()
{
}
