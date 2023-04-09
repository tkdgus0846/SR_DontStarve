#include "stdafx.h"
#include "CollisionMgr.h"

IMPLEMENT_SINGLETON(CCollisionMgr)

CCollisionMgr::CCollisionMgr()
{
	m_bIsRender = false;
}


CCollisionMgr::~CCollisionMgr()
{
	Free();
}

void CCollisionMgr::Check_Collision(COLGROUP ID1, COLGROUP ID2)
{
	if (m_ColliderList[ID1].empty())
		return;
	if (m_ColliderList[ID2].empty())
		return;

	for (auto iterID1 = m_ColliderList[ID1].begin(); iterID1 != m_ColliderList[ID1].end(); iterID1++)
	{
		for (auto iterID2 = m_ColliderList[ID2].begin(); iterID2 != m_ColliderList[ID2].end(); iterID2++)
		{
			if (ID1 == ID2 && iterID1 == iterID2) continue;

			CCollider* collider1 = *iterID1;
			CCollider* collider2 = *iterID2;
			
			auto* colliderList1 = &collider1->m_CollisionList;
			auto* colliderList2 = &collider2->m_CollisionList;
			auto findCollider = colliderList1->find(collider2);
			
			COL_DIR colDir;
			Collision collision1;
			Collision collision2;

			// 충돌했다면
			if (Collision_Box(collider1, collider2, collision1.CollisionDir, collision1.intersectBox, collision1.amountVec))
			{
				collision2 = collision1;
				collision2.CollisionDir = (COL_DIR)((int)collision2.CollisionDir * -1);

				collision1.MyCollider = collider1;
				collision1.OtherCollider = collider2;
				collision1.OtherGameObject = collider2->Get_GameObject();

				collision2.MyCollider = collider2;
				collision2.OtherCollider = collider1;
				collision2.OtherGameObject = collider1->Get_GameObject();

				// 둘이 충돌하고 있지 않았으면
				if (findCollider == colliderList1->end())
				{
					collider1->OnCollisionEnter(&collision1);
					collider1->OnCollisionStay(&collision1);

					collider2->OnCollisionEnter(&collision2);
					collider2->OnCollisionStay(&collision2);
				}
				// 둘이 충돌하고 있었으면
				else
				{
					collider1->OnCollisionStay(&collision1);
					collider2->OnCollisionStay(&collision2);
				}

				(*colliderList1)[collider2] = collision1;
				(*colliderList2)[collider1] = collision2;

			}
			// 충돌 하지 않았다면
			else 
			{
				if (colliderList1->empty()) continue;
				if (colliderList2->empty()) continue;

				if (findCollider != colliderList1->end())
				{
					auto findCollider2 = colliderList2->find(collider1);

					collider1->OnCollisionExit(&findCollider->second);
					collider2->OnCollisionExit(&findCollider2->second);

					colliderList1->erase(collider2);
					colliderList2->erase(collider1);
				}
			}
		}
	}
}

void CCollisionMgr::Add_Collider(COLGROUP eID, CCollider * pCollider)
{
	if (COL_END <= eID || nullptr == pCollider)
		return;
	m_ColliderList[eID].push_back(pCollider);

	if (m_bIsRender != pCollider->m_bIsRender)
		m_bIsRender = pCollider->m_bIsRender;
}

void CCollisionMgr::Change_ColGroup(CCollider* collider, COLGROUP changeID)
{
	list<CCollider*>::iterator iter;
	_bool found = false;
	for (int i = 0; i < COL_END; i++)
	{
		for (iter = m_ColliderList[i].begin(); iter != m_ColliderList[i].end(); ++iter)
		{
			if (*iter == collider)
			{
				m_ColliderList[i].erase(iter);
				found = true;
				break;
			}
		}
		if (found == true) break;
	}
	
	if (found == false) return;

	
	m_ColliderList[changeID].push_front(collider);
}

void Engine::CCollisionMgr::Toggle_ColliderRender()
{
	m_bIsRender = (m_bIsRender == false) ? true : false;
	for (int i = 0; i < COL_END; i++)
		for (auto col : m_ColliderList[i])
			col->Set_IsRender(m_bIsRender);
}

bool CCollisionMgr::Collision_Box(CCollider* pSrc, CCollider* pDest, COL_DIR& colDir, BoundingBox& bound, _vec3& amountVec)
{
	_float fX, fY, fZ;
	if (Check_BoundingBox(pSrc, pDest, &fX, &fY, &fZ))
	{
		amountVec = { fX, fY, fZ };

		_vec3 srcVec = pSrc->Get_BoundCenter() - pSrc->Get_BoundSize() / 2.f;
		_vec3 dstVec = pDest->Get_BoundCenter() - pDest->Get_BoundSize() / 2.f;

		_vec3 minVec = (srcVec.Length() < dstVec.Length()) ? dstVec : srcVec;

		srcVec = pSrc->Get_BoundCenter() + pSrc->Get_BoundSize() / 2.f;
		dstVec = pDest->Get_BoundCenter() + pDest->Get_BoundSize() / 2.f;

		_vec3 maxVec = (srcVec.Length() < dstVec.Length()) ? srcVec : dstVec;
		
		bound._min = minVec;
		bound._max = maxVec;
		bound._offsetMin = { 0.f,0.f,0.f };
		bound._offsetMax = maxVec - minVec;

		// src 기준
		if (fX > fY)
		{
			if (fZ > fY) // 상하
			{
				if (pSrc->Get_BoundCenter().y < pDest->Get_BoundCenter().y)
				{
					// 상충돌
					colDir = DIR_UP;
					return true;
				}
				else
				{
					// 하충돌
					colDir = DIR_DOWN;
					return true;
				}
			}
			
			if (fY > fZ) // 전후
			{
				if (pSrc->Get_BoundCenter().z < pDest->Get_BoundCenter().z)
				{
					// 후충돌
					colDir = DIR_FRONT;
					return true;
				}
				else
				{
					// 전충돌
					colDir = DIR_BACK;
					return true;
				}
			}
		}
		else
		{
			if (fZ > fX) // 좌우
			{
				if (pSrc->Get_BoundCenter().x < pDest->Get_BoundCenter().x)
				{
					// 우충돌
					colDir = DIR_RIGHT;
					return true;
				}
				else
				{
					// 좌충돌
					colDir = DIR_LEFT;
					return true;
				}
			}
			if (fX > fZ) // 전후
			{
				if (pSrc->Get_BoundCenter().z < pDest->Get_BoundCenter().z)
				{
					// 후충돌
					colDir = DIR_FRONT;
					return true;
				}
				else
				{
					// 전충돌
					colDir = DIR_BACK;
					return true;
				}
			}
		}
	}
	return false;
}

_bool CCollisionMgr::Check_BoundingBox(CCollider * pSrc, CCollider * pDest, _float * pX, _float * pY, _float * pZ)
{
	float	fX = fabs(pDest->Get_BoundCenter().x - pSrc->Get_BoundCenter().x);
	float	fY = fabs(pDest->Get_BoundCenter().y - pSrc->Get_BoundCenter().y);
	float	fZ = fabs(pDest->Get_BoundCenter().z - pSrc->Get_BoundCenter().z);

	float	fRadiusX = (pDest->Get_BoundSize().x + pSrc->Get_BoundSize().x) * 0.5f;
	float	fRadiusY = (pDest->Get_BoundSize().y + pSrc->Get_BoundSize().y) * 0.5f;
	float	fRadiusZ = (pDest->Get_BoundSize().z + pSrc->Get_BoundSize().z) * 0.5f;

	if ((fRadiusX > fX) && (fRadiusY > fY) && (fRadiusZ > fZ))
	{
		*pX = fRadiusX - fX;
		*pY = fRadiusY - fY;
		*pZ = fRadiusZ - fZ;
		return true;
	}

	return false;
}

void CCollisionMgr::Free(void)
{
	for (size_t i = 0; i < COL_END; ++i)
	{
		m_ColliderList[i].clear();
	}
}
