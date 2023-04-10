#pragma once
#include "Base.h"
#include "Collider.h"

BEGIN(Engine)

class CCollisionMgr : public CBase
{
	DECLARE_SINGLETON(CCollisionMgr)

private:
	explicit CCollisionMgr();
	virtual ~CCollisionMgr();

public:
	// 실질적으로 콜리젼을 체크해주는 함수.
	void		Check_Collision(COLGROUP ID1, COLGROUP ID2);
	void		Add_Collider(COLGROUP eID, CCollider* pCollider);
	// 콜라이더들의 렌더를 꺼주는 함수.
	void		Toggle_ColliderRender();
	void		Change_ColGroup(CCollider* collider, COLGROUP changeID);
	_bool		GetIsRender() const { return m_bIsRender; }
	void		Remove_Collider(CCollider* collider, COLGROUP colID);
	void		Remove_Collider(CGameObject* gameObject);

private:
	void		Find_Remove_Collider(CGameObject* gameObject, COLGROUP colID);
	bool		Collision_Box(CCollider* pSrc, CCollider* pDest, COL_DIR& colDir, BoundingBox& bound, _vec3& amountVec);
	_bool		Check_BoundingBox(CCollider * pSrc, CCollider * pDest, _float * pX, _float * pY, _float * pZ);
	
private:
	list<CCollider*>	m_ColliderList[COL_END];
	_bool				m_bIsRender;

private:
	virtual void Free(void) override;
};

END