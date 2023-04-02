#include "stdafx.h"
#include "BulletMgr.h"
#include "Bullet.h"

IMPLEMENT_SINGLETON(CBulletMgr)



CBulletPool::CBulletPool()
{
}

CBulletPool::~CBulletPool()
{
}

void CBulletPool::Push(CBullet * pObj)
{
	if (nullptr == pObj)
		return;

	m_BulletPool.push_back(pObj);
}

void CBulletPool::Free(void)
{
	for_each(m_BulletPool.begin(), m_BulletPool.end(), CDeleteObj());
	m_BulletPool.clear();
}



CBulletPool* CBulletPool::Create()
{
	CBulletPool*		pInstance = new CBulletPool();
	return pInstance;
}

CBulletMgr::CBulletMgr()
{
}


CBulletMgr::~CBulletMgr()
{
	Free();
}



void CBulletMgr::Push(const _tchar* name, CBullet* pBullet)
{
	if (m_BulletPool[name] == nullptr) return;

	m_BulletPool[name]->Push(pBullet);
}


void CBulletMgr::Free(void)
{
	for_each(m_BulletPool.begin(), m_BulletPool.end(), CDeleteMap());
	m_BulletPool.clear();
}


