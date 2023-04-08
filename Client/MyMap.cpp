#include "MyMap.h"

#include "Room.h"
#include "Export_Function.h"

CMyMap::CMyMap(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev), m_pTennel(nullptr)
{
	for (auto iter : m_arrRoom)
		iter = nullptr;
}

CMyMap::~CMyMap()
{
}

HRESULT CMyMap::Ready_GameObject(void)
{
	Create_Default_Room();

	return __super::Ready_GameObject();
}

_int CMyMap::Update_GameObject(const _float & fTimeDelta)
{
	for (auto Room : m_arrRoom)
		Room->Update_GameObject(fTimeDelta);

	m_pTennel->Update_GameObject(fTimeDelta);

	__super::Update_GameObject(fTimeDelta);

	return 0;
}

void CMyMap::LateUpdate_GameObject(void)
{
	for (auto Room : m_arrRoom)
		Room->LateUpdate_GameObject();

	m_pTennel->LateUpdate_GameObject();

	__super::LateUpdate_GameObject();
}

void CMyMap::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());

	__super::Render_GameObject();
}

HRESULT CMyMap::Add_Component()
{
	return S_OK;
}

void CMyMap::Create_Default_Room()
{
	for (_int i = 0; i < 25; ++i)
	{
		m_arrRoom[i] = CRoom::Create(m_pGraphicDev);
	}

	/*for (_uint i = 0; i < 5; ++i)
	{
		for (_uint j = 0; j < 5; ++j)
		{
			_uint iIndex = i * 5 + j;

			CRoom* pRoom = CRoom::Create(m_pGraphicDev);

			pRoom->m_pTransform->m_vInfo[INFO_POS] = { j * 50.01f, 0.f, i * 50.01f };
			pRoom->FloorSubSet();
			pRoom->PlaceSubSet();

			m_arrRoom[iIndex] = pRoom;
		}
	}*/

	m_pTennel = CRoom::Create(m_pGraphicDev, 3, 2, 10);
	m_pTennel->m_pTransform->m_vInfo[INFO_POS] = { -60.f, 0.f, -60.f };
	m_pTennel->FloorSubSet();
	m_pTennel->PlaceSubSet();
}

CRoom * CMyMap::Get_CurRoom(const _vec3& vPos)
{
	_int iX = _int(vPos.x / 50.f);
	_int iZ = _int(vPos.z / 50.f);

	_int iIndex = iZ * 5 + iX;

	return m_arrRoom[iIndex];
}

_bool CMyMap::WriteMapFile(HANDLE hFile, DWORD& dwByte)
{
	_int iSize = m_arrRoom.size();
	WriteFile(hFile, &iSize, sizeof(_int), &dwByte, nullptr);
	for (_int i = 0; i < iSize; ++i)
	{
		m_arrRoom[i]->WriteRoomFile(hFile, dwByte);
	}
	return true;
}

_bool CMyMap::ReadMapFile(HANDLE hFile, DWORD& dwByte)
{
	_int iSize;
	ReadFile(hFile, &iSize, sizeof(_int), &dwByte, nullptr);
	for (_int i = 0; i < iSize; ++i)
	{
		//m_arrRoom[i] = CRoom::Create(m_pGraphicDev);
		m_arrRoom[i]->ReadRoomFile(hFile, dwByte);
		m_arrRoom[i]->FloorSubSet();
		m_arrRoom[i]->PlaceSubSet();
	}

	return true;
}

CMyMap * CMyMap::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMyMap*		pInstance = new CMyMap(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CMyMap::Free()
{
	for (auto iter : m_arrRoom)
		Safe_Release(iter);
	Safe_Release(m_pTennel);

	Safe_Release(m_pTennel);

	__super::Free();
}