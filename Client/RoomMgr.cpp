#include "stdafx.h"
#include "RoomMgr.h"

#include "Tennel.h"
#include "Export_Function.h"

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
	m_pCurRoom = m_arrRoom[0];

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

	m_pTennel[0] = CTennel::Create(m_pGraphicDev);
	m_pTennel[0]->m_pTransform->m_vInfo[INFO_POS] = { -30.f, 0.f, -20.f };
	m_pTennel[0]->Set_Position(0);
	m_pTennel[1] = CTennel::Create(m_pGraphicDev);
	m_pTennel[1]->m_pTransform->m_vInfo[INFO_POS] = { -30.f, 0.f, -30.f };
	m_pTennel[1]->Set_Position(1);
}

CRoom * CRoomMgr::Get_CurRoom(const _vec3& vPos)
{
	_int iX = _int(vPos.x / 60.f);
	_int iZ = _int(vPos.z / 60.f);

	_int iIndex = iZ * 5 + iX;

	return m_arrRoom[iIndex];
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

void CRoomMgr::Free()
{
	for (auto Room : m_arrRoom)
		Safe_Release(Room);

	Safe_Release(m_pTennel[0]);
	Safe_Release(m_pTennel[1]);

	Safe_Release(m_pGraphicDev);
}