#include "stdafx.h"
#include "RoomMgr.h"

#include "Tennel.h"
#include "Layer.h"
#include "Export_Function.h"

#include "NubBoss.h"
#include "WalkerBoss.h"
#include "WormHead.h"
#include "WormBody.h"
#include "WormTail.h"
#include "Bub.h"
#include "Rub.h"
#include "Cryder.h"
#include "SoftPyramid.h"
#include "HardPyramid.h"
#include "Slider.h"
#include "ShopNpc.h"
#include "Tile.h"

IMPLEMENT_SINGLETON(CRoomMgr)

CRoomMgr::CRoomMgr()
	: m_pCurRoom(nullptr)
{
	for (auto iter : m_arrRoom)
		iter = nullptr;
}

CRoomMgr::~CRoomMgr()
{
	Free();
}

HRESULT CRoomMgr::Ready_RoomMgr(LPDIRECT3DDEVICE9 pGraphicDev)
{
	m_pGraphicDev = pGraphicDev;
	m_pGraphicDev->AddRef();
	Create_Default_Room();
	

	return S_OK;
}

void CRoomMgr::Create_Default_Room()
{
	for (_uint i = 0; i < 5; ++i)
	{
		for (_uint j = 0; j < 5; ++j)
		{
			_uint iIndex = i * 5 + j;

			CRoom* pRoom = CRoom::Create(m_pGraphicDev);

			pRoom->m_pTransform->m_vInfo[INFO_POS] = { j * 60.01f, 0.f, i * 60.01f };
			pRoom->FloorSubSet();
			pRoom->PlaceSubSet();

			m_arrRoom[iIndex] = pRoom;
		}
	}

	m_pCurRoom = m_arrRoom[0];

	//====== 임시 코드임 =======

	//NPC 잠깐 넣어놓음
	m_arrRoom[1]->PushBack_GameObj(CShopNpc::Create(m_pGraphicDev));

	CWormHead* pHead = CWormHead::Create(m_pGraphicDev, _vec3(17.f, 2.f, 17.f));
	m_arrRoom[0]->PushBack_GameObj(pHead);

	m_arrRoom[0]->Set_DoorType(DOOR_NE);
	m_arrRoom[1]->Set_DoorType(DOOR_NW);
	m_arrRoom[5]->Set_DoorType(DOOR_ES);

	m_arrRoom[6]->Set_DoorType(DOOR_SW);

	m_arrRoom[0]->PushBack_GameObj(CWalkerBoss::Create(m_pGraphicDev, _vec3(40.f, 3.f, 40.f)));

	/*m_arrRoom[0]->PushBack_GameObj(CBub::Create(m_pGraphicDev));

	m_arrRoom[0]->PushBack_GameObj(CBub::Create(m_pGraphicDev));

	m_arrRoom[0]->PushBack_GameObj(CBub::Create(m_pGraphicDev, _vec3(30.f, -3.f, 40.f)));
	m_arrRoom[0]->PushBack_GameObj(CBub::Create(m_pGraphicDev, _vec3(20.f, -3.f, 40.f)));
//
//
//	
//
	m_arrRoom[0]->PushBack_GameObj(CBub::Create(m_pGraphicDev, _vec3(40.f, 1.f, 40.f)));
	m_arrRoom[0]->PushBack_GameObj(CRub::Create(m_pGraphicDev, _vec3(90.f, 2.4f, 40.f)));
	m_arrRoom[0]->PushBack_GameObj(CCryder::Create(m_pGraphicDev, _vec3(40.f, 0.6f, 40.f)));
	m_arrRoom[0]->PushBack_GameObj(CNubBoss::Create(m_pGraphicDev, _vec3(100.f, 0.6f, 40.f)));

//====== 임시 코드임 =======
	

}

void CRoomMgr::Set_CurRoom(const _uint iIndex)
{
	m_pCurRoom = m_arrRoom[iIndex];
}

void CRoomMgr::Set_Tennel(CTennel* tennel, _int iIndex)
{
	m_pTennel[iIndex] = tennel;
}

_bool CRoomMgr::WriteMapFile(HANDLE hFile, DWORD& dwByte)
{
	_int iSize = m_arrRoom.size();
	WriteFile(hFile, &iSize, sizeof(_int), &dwByte, nullptr);
	for (_int i = 0; i < iSize; ++i)
	{
		m_arrRoom[i]->WriteRoomFile(hFile, dwByte);
	}
	return true;
}

_bool CRoomMgr::ReadMapFile(HANDLE hFile, DWORD& dwByte)
{
	_int iSize;
	ReadFile(hFile, &iSize, sizeof(_int), &dwByte, nullptr);
	for (_int i = 0; i < iSize; ++i)
	{
		m_arrRoom[i]->ReadRoomFile(hFile, dwByte);
		m_arrRoom[i]->FloorSubSet();
		m_arrRoom[i]->PlaceSubSet();
	}

	return true;
}

vector<CLayer*>* CRoomMgr::Get_CurLayerVec()
{
	return m_pCurRoom->GetLayerVec();
}

list<CCollider*>* CRoomMgr::Get_CurColliderList(_int iIndex)
{
	return m_pCurRoom->GetColliderList(iIndex);
}

void CRoomMgr::Free()
{
	for (auto Room : m_arrRoom)
	{
		CManagement::GetInstance()->Set_StaticLayerArr(Room->GetLayerVec());
		for (int i = 0; i < COL_STATIC_END; i++)
		{
			CCollisionMgr::GetInstance()->Set_StaticColliderList(Room->GetColliderList(i), i);
		}
		Safe_Release(Room);
	}
		


	Safe_Release(m_pGraphicDev);
}