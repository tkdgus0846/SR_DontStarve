#include "stdafx.h"
#include "NormalBullet.h"

#include "Export_Function.h"
#include "BulletMgr.h"

CNormalBullet::CNormalBullet(LPDIRECT3DDEVICE9 pGraphicDev) :
	CBullet(pGraphicDev)
{
	m_fSpeed = 30.f;
	m_fLifeSpan = 2.f;
	m_fAge = 0.f;
}

CNormalBullet::~CNormalBullet()
{
}

void CNormalBullet::SetDead()
{
	CBulletMgr::GetInstance()->Push(L"NormalBullet", this);
}

HRESULT CNormalBullet::Ready_GameObject(void)
{
	
	return S_OK;
}

_int CNormalBullet::Update_GameObject(const _float& fTimeDelta)
{
	if (Aging(fTimeDelta) == OBJ_RETPOOL) return OBJ_RETPOOL;
	
	__super::Update_GameObject(fTimeDelta);
	m_pTransform->Move_Walk(m_fSpeed*2.f, fTimeDelta);

	Add_RenderGroup(RENDER_PRIORITY, this);

	return OBJ_NOEVENT;
}

void CNormalBullet::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CNormalBullet::Render_GameObject(void)
{
	__super::Render_GameObject();
}

void CNormalBullet::OnCollisionEnter(const class Collision* collsion)
{
	
}

void CNormalBullet::OnCollisionStay(const class Collision* collision)
{
	
}

void CNormalBullet::OnCollisionExit(const class Collision* collision)
{
	
}

void CNormalBullet::OnTriggerEnter(const class CCollider* other)
{
	
}

void CNormalBullet::OnTriggerStay(const class CCollider* other)
{
	
}

void CNormalBullet::OnTirggerExit(const class CCollider* other)
{
	
}

void CNormalBullet::Free(void)
{
	__super::Free();
}

CNormalBullet* CNormalBullet::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CNormalBullet*		pInstance = new CNormalBullet(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}
