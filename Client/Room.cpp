#include "stdafx.h"
#include "Room.h"

#include "Export_Function.h"

#include "Floor.h"
#include "Wall.h"
#include "Tile.h"
#include "Door.h"

CRoom::CRoom(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev), m_fVtxCntX(0.f), 
	m_fVtxCntZ(0.f), m_fVtxItv(0.f)
{
	for (auto& iter : m_apDoor)
	{
		iter.first = false;
		iter.second = nullptr;
	}
}

CRoom::~CRoom()
{
}

HRESULT CRoom::Ready_GameObject(const _float& fVtxCntX, const _float& fVtxCntZ, const _float& fVtxItv)
{
	m_fVtxItv = fVtxItv;
	m_fVtxCntX = fVtxCntX;
	m_fVtxCntZ = fVtxCntZ;

	HRESULT result = __super::Ready_GameObject();
	FAILED_CHECK_RETURN(CreateSubset(), E_FAIL);

	return result;
}

_int CRoom::Update_GameObject(const _float& fTimeDelta)
{
	__super::Update_GameObject(fTimeDelta);

	__super::Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	m_pFloor->Update_GameObject(fTimeDelta);
	for (auto& iter : m_apWall)
		iter->Update_GameObject(fTimeDelta);

	for (auto& iter : m_apDoor)
	{
		if (nullptr != iter.second)
			iter.second->Update_GameObject(fTimeDelta);
	}

	for (auto& Tile : m_vecTile)
		Tile->Update_GameObject(fTimeDelta);

	return 0;
}

void CRoom::LateUpdate_GameObject(void)
{
	// �� Ư���� Ʈ������ �ܿ� �Ⱦ��Ű��Ƽ� �ϴ� �ּ�ó��
	//__super::LateUpdate_GameObject();

	m_pFloor->LateUpdate_GameObject();
	for (auto& iter : m_apWall)
		iter->LateUpdate_GameObject();

	for (auto& Tile : m_vecTile)
		Tile->LateUpdate_GameObject();

}

void CRoom::Render_GameObject(void)
{
	// �� Ư���� Ʈ������ �ܿ� �Ⱦ��Ű��Ƽ� �ϴ� �ּ�ó��
	//__super::Render_GameObject();

	m_pFloor->Render_GameObject();
	for (auto& iter : m_apWall)
		iter->Render_GameObject();

	for (auto& Tile : m_vecTile)
		Tile->Render_GameObject();
}

HRESULT CRoom::CreateSubset()
{
	// �ٴ� ����
	m_pFloor = CFloor::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(m_pFloor, E_FAIL);

	// �� 4�� ����
	for (auto& iter : m_apWall)
		iter = CWall::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(m_apWall[0], E_FAIL);

	return S_OK;
}

void CRoom::Set_DoorType(DOOR_TYPE eType)
{
	m_eDoorType = eType;

	switch (m_eDoorType)
	{
	case DOOR_ES:
		m_apDoor[DOOR_RIGHT].first = true;
		m_apDoor[DOOR_DOWN].first = true;
		m_apDoor[DOOR_UP].first = false;
		m_apDoor[DOOR_LEFT].first = false;
		break;
	case DOOR_ESW:
		m_apDoor[DOOR_RIGHT].first = true;
		m_apDoor[DOOR_DOWN].first = true;
		m_apDoor[DOOR_LEFT].first = true;
		m_apDoor[DOOR_UP].first = false;
		break;
	case DOOR_EW:
		m_apDoor[DOOR_RIGHT].first = true;
		m_apDoor[DOOR_LEFT].first = true;
		m_apDoor[DOOR_UP].first = false;
		m_apDoor[DOOR_DOWN].first = false;
		break;
	case DOOR_N:
		m_apDoor[DOOR_UP].first = true;
		m_apDoor[DOOR_DOWN].first = false;
		m_apDoor[DOOR_LEFT].first = false;
		m_apDoor[DOOR_RIGHT].first = false;
		break;
	case DOOR_NE:
		m_apDoor[DOOR_UP].first = true;
		m_apDoor[DOOR_RIGHT].first = true;
		m_apDoor[DOOR_LEFT].first = false;
		m_apDoor[DOOR_DOWN].first = false;
		break;
	case DOOR_NES:
		m_apDoor[DOOR_UP].first = true;
		m_apDoor[DOOR_RIGHT].first = true;
		m_apDoor[DOOR_DOWN].first = true;
		m_apDoor[DOOR_LEFT].first = false;
		break;
	case DOOR_NESW:
		m_apDoor[DOOR_UP].first = true;
		m_apDoor[DOOR_RIGHT].first = true;
		m_apDoor[DOOR_DOWN].first = true;
		m_apDoor[DOOR_LEFT].first = true;
		break;
	case DOOR_NS:
		m_apDoor[DOOR_UP].first = true;
		m_apDoor[DOOR_DOWN].first = true;
		m_apDoor[DOOR_LEFT].first = false;
		m_apDoor[DOOR_RIGHT].first = false;
		break;
	case DOOR_NW:
		m_apDoor[DOOR_UP].first = true;
		m_apDoor[DOOR_LEFT].first = true;
		m_apDoor[DOOR_RIGHT].first = false;
		m_apDoor[DOOR_DOWN].first = false;
		break;
	case DOOR_S:
		m_apDoor[DOOR_DOWN].first = true;
		m_apDoor[DOOR_UP].first = false;
		m_apDoor[DOOR_LEFT].first = false;
		m_apDoor[DOOR_RIGHT].first = false;
		break;
	case DOOR_SW:
		m_apDoor[DOOR_DOWN].first = true;
		m_apDoor[DOOR_LEFT].first = true;
		m_apDoor[DOOR_UP].first = false;
		m_apDoor[DOOR_RIGHT].first = false;
		break;
	case DOOR_SWN:
		m_apDoor[DOOR_DOWN].first = true;
		m_apDoor[DOOR_LEFT].first = true;
		m_apDoor[DOOR_UP].first = true;
		m_apDoor[DOOR_RIGHT].first = false;
		break;
	case DOOR_W:
		m_apDoor[DOOR_LEFT].first = true;
		m_apDoor[DOOR_RIGHT].first = false;
		m_apDoor[DOOR_UP].first = false;
		m_apDoor[DOOR_DOWN].first = false;
		break;
	case DOOR_WNE:
		m_apDoor[DOOR_LEFT].first = true;
		m_apDoor[DOOR_UP].first = true;
		m_apDoor[DOOR_RIGHT].first = true;
		m_apDoor[DOOR_DOWN].first = false;
		break;
	case DOOR_E:
		m_apDoor[DOOR_RIGHT].first = true;
		m_apDoor[DOOR_UP].first = false;
		m_apDoor[DOOR_DOWN].first = false;
		m_apDoor[DOOR_LEFT].first = false;
		break;
	}
	for (_uint i = 0; i < 4; ++i)
	{
		if (true == m_apDoor[i].first)
		{
			if (nullptr == m_apDoor[i].second)
			{
				_vec3 vPos(0.f, 0.f, 0.f);
				_vec3 vCurRoomPos = m_pTransform->m_vInfo[INFO_POS];
				_bool IsRot = false;
				switch (i)
				{
				case Engine::DOOR_UP:
					vPos = { vCurRoomPos.x + 25.f, 3.f, vCurRoomPos.z + 49.9f };
					break;

				case Engine::DOOR_DOWN:
					vPos = { vCurRoomPos.x + 25.f, 3.f, vCurRoomPos.z + 0.1f };
					break;

				case Engine::DOOR_LEFT:
					vPos = { vCurRoomPos.x + 0.1f, 3.f, vCurRoomPos.z + 25.f };
					IsRot = true;
					break;

				case Engine::DOOR_RIGHT:
					vPos = { vCurRoomPos.x + 49.9f, 3.f, vCurRoomPos.z + 25.f };
					IsRot = true;
					break;
				}
				m_apDoor[i].second = CDoor::Create(m_pGraphicDev, vPos, IsRot);
			}
		}
		else if (nullptr != m_apDoor[i].second)
			Safe_Release(m_apDoor[i].second);
	}
}

void CRoom::FloorSubSet()
{
	// �ٴ� ��ġ ����
	_vec3 vPos;
	m_pTransform->Get_Info(INFO_POS, &vPos);

	m_pFloor->m_pTransform->Set_Pos(vPos);
}

void CRoom::PlaceSubSet()	
{
	const _float colliderThick = 4.f;

	// �� ��ġ ����
	_vec3 vPos;
	float fLengthX = (m_fVtxCntX - 1) * m_fVtxItv;
	float fLengthZ = (m_fVtxCntZ - 1) * m_fVtxItv;
	float fLengthY = VTXITV;

	m_pTransform->Get_Info(INFO_POS, &vPos);

	m_apWall[0]->m_pTransform->Set_Pos(vPos);
	m_apWall[1]->m_pTransform->Set_Pos(vPos.x, vPos.y, vPos.z + fLengthZ);
	m_apWall[2]->m_pTransform->Set_Pos(vPos.x + fLengthX, vPos.y, vPos.z + fLengthZ);
	m_apWall[3]->m_pTransform->Set_Pos(vPos.x + fLengthX, vPos.y, vPos.z);

	m_apWall[1]->m_pTransform->Set_Target({ vPos.x + fLengthX, vPos.y, vPos.z + fLengthZ });
	m_apWall[2]->m_pTransform->Set_Target({ vPos.x + fLengthX, vPos.y, vPos.z });
	m_apWall[3]->m_pTransform->Set_Target(vPos);

	_float width, height, depth;
	_vec3 centerPos;
	height = fLengthY;

	width = fLengthX;
	depth = colliderThick;
	centerPos = { + width / 2.f, + height / 2.f, - depth / 2.f};
	m_apWall[0]->m_pCollider->Set_BoundingBox({ width,height,depth }, centerPos);

	width = colliderThick;
	depth = fLengthZ;
	centerPos = { - width / 2.f, + height / 2.f, - depth/2.f };
	m_apWall[1]->m_pCollider->Set_BoundingBox({ width,height,depth }, centerPos);

	width = fLengthX;
	depth = colliderThick;
	centerPos = { - width / 2.f, + height / 2.f,+ depth/2.f  };
	m_apWall[2]->m_pCollider->Set_BoundingBox({ width,height,depth }, centerPos);

	width = colliderThick;
	depth = fLengthZ;
	centerPos = { + width / 2.f, + height / 2.f, + depth/2.f };
	m_apWall[3]->m_pCollider->Set_BoundingBox({ width,height,depth }, centerPos);
}

_bool CRoom::WriteRoomFile(HANDLE hFile, DWORD& dwByte)
{
	_int iSize = m_vecTile.size();

	WriteFile(hFile, &m_fVtxCntX, sizeof(_float), &dwByte, nullptr);
	WriteFile(hFile, &m_fVtxCntZ, sizeof(_float), &dwByte, nullptr);
	WriteFile(hFile, &m_fVtxItv, sizeof(_float), &dwByte, nullptr);
	m_pTransform->WriteTransformFile(hFile, dwByte);
	
	WriteFile(hFile, &iSize, sizeof(_int), &dwByte, nullptr);
	for (_int i = 0; i < iSize; ++i)
		m_vecTile[i]->m_pTransform->WriteTransformFile(hFile, dwByte);
	
	return true;
}

_bool CRoom::ReadRoomFile(HANDLE hFile, DWORD & dwByte)
{
	_int iSize;
	ReadFile(hFile, &m_fVtxCntX, sizeof(_float), &dwByte, nullptr);
	ReadFile(hFile, &m_fVtxCntZ, sizeof(_float), &dwByte, nullptr);
	ReadFile(hFile, &m_fVtxItv, sizeof(_float), &dwByte, nullptr);
	m_pTransform->ReadTransformFile(hFile, dwByte);

	ReadFile(hFile, &iSize, sizeof(_int), &dwByte, nullptr);
	for (_int i = 0; i < iSize; ++i)
	{
		m_vecTile.push_back(CTile::Create(m_pGraphicDev, _vec3{ 0.f, 0.f, 0.f }, L"Floor_Level1_Texture"));
		m_vecTile[i]->m_pTransform->ReadTransformFile(hFile, dwByte);
	}

	return true;
}

HRESULT CRoom::Add_Component(void)
{
	return S_OK;
}

CRoom* CRoom::Create(LPDIRECT3DDEVICE9 pGraphicDev,
	const _float& fVtxCntX, const _float& fVtxCntZ, const _float& fVtxItv)
{
	CRoom*		pInstance = new CRoom(pGraphicDev);
	
	if (FAILED(pInstance->Ready_GameObject(fVtxCntX, fVtxCntZ, fVtxItv)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CRoom::Free(void)
{
	Safe_Release(m_pFloor);
	for (auto& iter : m_apWall)
		Safe_Release(iter);
	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Release<CTile*>);

	for (auto& iter : m_apDoor)
		Safe_Release(iter.second);

	__super::Free();
}

