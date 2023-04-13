#include "stdafx.h"
#include "RoomMgr.h"

#include "Tennel.h"
#include "Layer.h"
#include "Export_Function.h"

#include "Bub.h"
#include "SoftPyramid.h"
#include "HardPyramid.h"
#include "Slider.h"

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

//_int CRoomMgr::Update_GameObject(const _float & fTimeDelta)
//{
//	if (!m_arrRoom[0])
//		return 0;
//
//	for (auto iter : m_arrRoom)
//		iter->Update_GameObject(fTimeDelta);
//
//	CGameObject* pPlayer = Get_Player();
//	if (nullptr == pPlayer)	// 에디터 모드
//	{
//		for (auto iter : m_arrRoom)
//			iter->Update_GameObject(fTimeDelta);
//	}
//	else	// 인 게임
//		m_pCurRoom->Update_GameObject(fTimeDelta);
//
//	m_pTennel[0]->Update_GameObject(fTimeDelta);
//	m_pTennel[1]->Update_GameObject(fTimeDelta);
//
//
//	return 0;
//}
//
//void CRoomMgr::LateUpdate_GameObject(void)
//{
//	if (!m_arrRoom[0])
//		return;
//
//	CGameObject* pPlayer = Get_Player();
//	if (nullptr == pPlayer)	// 에디터 모드
//	{
//		for (auto iter : m_arrRoom)
//			iter->LateUpdate_GameObject();
//	}
//	else	// 인 게임
//		m_pCurRoom->LateUpdate_GameObject();
//
//	m_pTennel[0]->LateUpdate_GameObject();
//	m_pTennel[1]->LateUpdate_GameObject();
//
//}
//
//void CRoomMgr::Render_GameObject(void)
//{
//	if (!m_arrRoom[0])
//		return;
//
//	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
//}


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
	m_arrRoom[0]->Set_DoorType(DOOR_NE);
	m_arrRoom[1]->Set_DoorType(DOOR_NW);
	m_arrRoom[5]->Set_DoorType(DOOR_ES);
	m_arrRoom[6]->Set_DoorType(DOOR_SW);

	m_arrRoom[0]->PushBack_GameObj(CBub::Create(m_pGraphicDev, _vec3(40.f, 0.6f, 40.f)));
	m_arrRoom[0]->PushBack_GameObj(CBub::Create(m_pGraphicDev, _vec3(35.f, 0.6f, 40.f)));

	m_arrRoom[0]->PushBack_GameObj(CSoftPyramid::Create(m_pGraphicDev));
	m_arrRoom[0]->PushBack_GameObj(CSlider::Create(m_pGraphicDev));
	//m_arrRoom[0]->PushBack_GameObj(CHardPyramid::Create(m_pGraphicDev));

	m_arrRoom[0]->PushBack_GameObj(CBub::Create(m_pGraphicDev, _vec3(41.f, 0.6f, 41.f)));
	m_arrRoom[0]->PushBack_GameObj(CBub::Create(m_pGraphicDev, _vec3(32.f, 0.6f, 40.f)));
	m_arrRoom[0]->PushBack_GameObj(CBub::Create(m_pGraphicDev, _vec3(30.f, 0.6f, 40.f)));
	m_arrRoom[0]->PushBack_GameObj(CBub::Create(m_pGraphicDev, _vec3(32.f, 0.6f, 43.f)));
	m_arrRoom[0]->PushBack_GameObj(CBub::Create(m_pGraphicDev, _vec3(40.f, 0.6f, 40.f)));
	m_arrRoom[0]->PushBack_GameObj(CBub::Create(m_pGraphicDev, _vec3(35.f, 0.6f, 40.f)));


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
		Safe_Release(Room);


	Safe_Release(m_pGraphicDev);
}