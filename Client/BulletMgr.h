#pragma once
#include "Base.h"
#include "Bullet.h"
#include "Export_Function.h"

class CBulletPool : public CBase
{
	friend class CBulletMgr;

private:
	CBulletPool();
	~CBulletPool();

	template<typename T>
	CBullet* CBulletPool::Pop(LPDIRECT3DDEVICE9 pDevice, const _vec3 & vPos, const _vec3 & vDir, const _vec3& vScale = { 1.f,1.f,1.f }, bool bIsEnemyBullet = false)
	{
		CBullet*		pBullet = nullptr;

		if (m_BulletPool.empty())
		{
			pBullet = T::Create(pDevice);
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

		CCollider* collider = dynamic_cast<CCollider*>(pBullet->Get_Component(L"BodyCollider", ID_ALL));
		if (collider == nullptr) return pBullet;
		_bool bIsRender = Engine::Collider_GetIsRender();
		collider->Set_IsRender(bIsRender);

		if (bIsEnemyBullet == true)
		{
			Engine::Change_ColGroup(collider, COL_ENEMYBULLET);
		}
		else
		{
			Engine::Change_ColGroup(collider, COL_PLAYERBULLET);
		}

		return pBullet;
	}

	void		Push(CBullet* pObj);

	list<CBullet*>		m_BulletPool;
	int				m_iCreateCnt = 0;

	virtual void Free(void) override;
	static CBulletPool* Create();

};

// �Ѿ� ������Ʈ Ǯ �Ŵ���
class CBulletMgr : public CBase
{
	DECLARE_SINGLETON(CBulletMgr)
private:
	explicit CBulletMgr();
	virtual ~CBulletMgr();

public:

	void Reserve(_uint cnt) 
	{
		
	}

	template<typename T>
	T * CBulletMgr::Pop(const _tchar* name, LPDIRECT3DDEVICE9 pDevice, const _vec3& vPos, const _vec3& vDir, const _vec3& vScale = { 1.f,1.f,1.f }, bool bIsEnemyBullet = false)
	{
		if (m_BulletPool[name] == nullptr)
		{
			m_BulletPool[name] = CBulletPool::Create();
		}
		CBullet*		pBullet = m_BulletPool[name]->Pop<T>(pDevice, vPos, vDir, vScale, bIsEnemyBullet);
		if (pBullet == nullptr)
			return nullptr;

		return dynamic_cast<T*>(pBullet);
	}
	void		Push(const _tchar* name, CBullet* pBullet);

	virtual void Free(void) override;

private:
	unordered_map<const _tchar*, CBulletPool*> m_BulletPool;
};


