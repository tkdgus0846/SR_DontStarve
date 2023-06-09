#include "stdafx.h"
#include "BulletMgr.h"
#include "NormalBullet.h"
#include "FireBullet.h"
#include "IceBullet.h"
#include "VortexBullet.h"

IMPLEMENT_SINGLETON(CBulletMgr)



CBulletPool::CBulletPool()
{
}

CBulletPool::~CBulletPool()
{
	//Free();
}

void CBulletPool::Push(CBullet * pObj)
{
	if (nullptr == pObj)
		return;

	auto colNameVec = pObj->Get_ColNameVec();

	for (int i = 0; i < colNameVec.size(); i++)
	{
		CCollider* collider = dynamic_cast<CCollider*>(pObj->Get_Component(colNameVec[i], ID_ALL));

		if (collider == nullptr) continue;

		collider->Set_Enable(FALSE);
	}

	m_BulletPool.push_back(pObj);
}

void CBulletPool::Free(void)
{
	for_each(m_BulletPool.begin(), m_BulletPool.end(), CDeleteObj());
	m_BulletPool.clear();
}

//////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

CBulletPool* CBulletPool::Create()
{
	CBulletPool*		pInstance = new CBulletPool();
	return pInstance;
}

CBullet* CBulletPool::Pop(const _tchar* name, LPDIRECT3DDEVICE9 pDevice, const _vec3 & vPos, const _vec3 & vDir, const _vec3& vScale, bool bIsEnemyBullet)
{
	CBullet*		pBullet = nullptr;

	if (m_BulletPool.empty())
	{
		if (name == L"FireBullet")
		{
			pBullet = CFireBullet::Create(pDevice);
		}
		else if (name == L"NormalBullet")
		{
			pBullet = CNormalBullet::Create(pDevice);
		}
		else if (name == L"IceBullet")
		{
			pBullet = CIceBullet::Create(pDevice);
		}
		else if (name == L"VortexBullet")
		{
			pBullet = CVortexBullet::Create(pDevice);
		}
		++m_iCreateCnt;
		//cout << m_iCreateCnt << endl;
	}

	else
	{
		pBullet = m_BulletPool.front();
		m_BulletPool.pop_front();
	}

	if (nullptr == pBullet)
		return nullptr;

	(pBullet)->Set_Pos(vPos);
	(pBullet)->Set_Dir(vDir);
	(pBullet)->SetIsEnemy(bIsEnemyBullet);
	(pBullet)->SetAge();
	(pBullet)->SetDead(false);
	(pBullet)->m_pTransform->Set_Scale(vScale);
	(pBullet)->Pop_Initialize();

	Engine::Add_Collider(pBullet);


	auto colNameVec = pBullet->Get_ColNameVec();
	_bool bIsRender = Engine::Collider_GetIsRender();

	for (int i = 0; i < colNameVec.size(); i++)
	{
		CCollider* collider = dynamic_cast<CCollider*>(pBullet->Get_Component(colNameVec[i], ID_ALL));

		if (collider == nullptr) continue;

		collider->Set_Enable(TRUE);
		collider->Set_IsRender(bIsRender);

		if (bIsEnemyBullet == true)
		{
			Engine::Change_ColGroup(collider, COL_ENEMYBULLET);
		}
		else
		{
			Engine::Change_ColGroup(collider, COL_PLAYERBULLET);
		}
	}	

	

	return pBullet;
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

CBullet* CBulletMgr::Pop(const _tchar* name, LPDIRECT3DDEVICE9 pDevice, const _vec3& vPos, const _vec3& vDir, const _vec3& vScale, bool bIsEnemyBullet)
{
	if (m_BulletPool[name] == nullptr)
	{
		m_BulletPool[name] = CBulletPool::Create();
	}
	CBullet*		pBullet = m_BulletPool[name]->Pop(name, pDevice, vPos, vDir, vScale, bIsEnemyBullet);
	if (pBullet == nullptr)
		return nullptr;

	return pBullet;
}

