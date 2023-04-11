#include "stdafx.h"
#include "Room.h"
#include "Baller.h"
#include "Bub.h"
#include "Guppi.h"
#include "Turret.h"
#include "Walker.h"
#include "Export_Function.h"
#include "Layer.h"

#include "Floor.h"
#include "Wall.h"
#include "Tile.h"
#include "Door.h"


CRoom::CRoom(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev), m_fVtxCntX(0.f), 
	m_fVtxCntZ(0.f), m_fVtxItv(0.f)
	, m_pFloor(nullptr)
{	
	for (auto& iter : m_apDoor)
	{
		iter.first = false;
		iter.second = nullptr;
	}

	for (auto& iter : m_apWall)
	{
		iter = nullptr;
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
	
	for (int i = 0; i < LAYER_STATIC_END; i++)
		m_vecLayer.push_back(CLayer::Create());

	HRESULT result = __super::Ready_GameObject();
	FAILED_CHECK_RETURN(CreateSubset(), E_FAIL);
	
	return result;
}

_int CRoom::Update_GameObject(const _float& fTimeDelta)
{
	return 0;
}

void CRoom::LateUpdate_GameObject(void)
{
}

void CRoom::Render_GameObject(void)
{
}

HRESULT CRoom::CreateSubset()
{
	// 바닥 생성
	m_pFloor = CFloor::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(m_pFloor, E_FAIL);
	PushBack_GameObj(m_pFloor);

	//// 벽 4면 생성
	for (auto& iter : m_apWall) {
		iter = CWall::Create(m_pGraphicDev);
		PushBack_GameObj(iter);
	}
	NULL_CHECK_RETURN(m_apWall[0], E_FAIL);

	return S_OK;
}

void CRoom::FreeSubset()
{
	for_each(m_vecLayer.begin(), m_vecLayer.end(), CDeleteObj());
}

void CRoom::Set_DoorType(DOOR_TYPE eType)
{
	m_eDoorType = eType;

	switch (m_eDoorType)
	{
	case DOOR_ES:
		m_apDoor[DOOR_EAST].first = true;
		m_apDoor[DOOR_SOUTH].first = true;
		m_apDoor[DOOR_NORTH].first = false;
		m_apDoor[DOOR_WEST].first = false;
		break;
	case DOOR_ESW:
		m_apDoor[DOOR_EAST].first = true;
		m_apDoor[DOOR_SOUTH].first = true;
		m_apDoor[DOOR_WEST].first = true;
		m_apDoor[DOOR_NORTH].first = false;
		break;
	case DOOR_EW:
		m_apDoor[DOOR_EAST].first = true;
		m_apDoor[DOOR_WEST].first = true;
		m_apDoor[DOOR_NORTH].first = false;
		m_apDoor[DOOR_SOUTH].first = false;
		break;
	case DOOR_N:
		m_apDoor[DOOR_NORTH].first = true;
		m_apDoor[DOOR_SOUTH].first = false;
		m_apDoor[DOOR_WEST].first = false;
		m_apDoor[DOOR_EAST].first = false;
		break;
	case DOOR_NE:
		m_apDoor[DOOR_NORTH].first = true;
		m_apDoor[DOOR_EAST].first = true;
		m_apDoor[DOOR_WEST].first = false;
		m_apDoor[DOOR_SOUTH].first = false;
		break;
	case DOOR_NES:
		m_apDoor[DOOR_NORTH].first = true;
		m_apDoor[DOOR_EAST].first = true;
		m_apDoor[DOOR_SOUTH].first = true;
		m_apDoor[DOOR_WEST].first = false;
		break;
	case DOOR_NESW:
		m_apDoor[DOOR_NORTH].first = true;
		m_apDoor[DOOR_EAST].first = true;
		m_apDoor[DOOR_SOUTH].first = true;
		m_apDoor[DOOR_WEST].first = true;
		break;
	case DOOR_NS:
		m_apDoor[DOOR_NORTH].first = true;
		m_apDoor[DOOR_SOUTH].first = true;
		m_apDoor[DOOR_WEST].first = false;
		m_apDoor[DOOR_EAST].first = false;
		break;
	case DOOR_NW:
		m_apDoor[DOOR_NORTH].first = true;
		m_apDoor[DOOR_WEST].first = true;
		m_apDoor[DOOR_EAST].first = false;
		m_apDoor[DOOR_SOUTH].first = false;
		break;
	case DOOR_S:
		m_apDoor[DOOR_SOUTH].first = true;
		m_apDoor[DOOR_NORTH].first = false;
		m_apDoor[DOOR_WEST].first = false;
		m_apDoor[DOOR_EAST].first = false;
		break;
	case DOOR_SW:
		m_apDoor[DOOR_SOUTH].first = true;
		m_apDoor[DOOR_WEST].first = true;
		m_apDoor[DOOR_NORTH].first = false;
		m_apDoor[DOOR_EAST].first = false;
		break;
	case DOOR_SWN:
		m_apDoor[DOOR_SOUTH].first = true;
		m_apDoor[DOOR_WEST].first = true;
		m_apDoor[DOOR_NORTH].first = true;
		m_apDoor[DOOR_EAST].first = false;
		break;
	case DOOR_W:
		m_apDoor[DOOR_WEST].first = true;
		m_apDoor[DOOR_EAST].first = false;
		m_apDoor[DOOR_NORTH].first = false;
		m_apDoor[DOOR_SOUTH].first = false;
		break;
	case DOOR_WNE:
		m_apDoor[DOOR_WEST].first = true;
		m_apDoor[DOOR_NORTH].first = true;
		m_apDoor[DOOR_EAST].first = true;
		m_apDoor[DOOR_SOUTH].first = false;
		break;
	case DOOR_E:
		m_apDoor[DOOR_EAST].first = true;
		m_apDoor[DOOR_NORTH].first = false;
		m_apDoor[DOOR_SOUTH].first = false;
		m_apDoor[DOOR_WEST].first = false;
		break;
	}
	for (_uint i = 0; i < 4; ++i)
	{
		if (true == m_apDoor[i].first)
		{
			if (nullptr == m_apDoor[i].second)
			{
				m_apDoor[i].second = CDoor::Create(m_pGraphicDev, (DOOR_DIR)i, this);
				PushBack_GameObj(m_apDoor[i].second);
			}
		}
		else if (nullptr != m_apDoor[i].second)
			m_apDoor[i].second->SetDead();

	}
}

_int CRoom::Get_Room_Index()
{
	_int iX = _int(m_pTransform->m_vInfo[INFO_POS].x / 60.f);
	_int iZ = _int(m_pTransform->m_vInfo[INFO_POS].z / 60.f);

	return iZ * 5 + iX;
}

void CRoom::FloorSubSet()
{
	// 바닥 위치 조정
	_vec3 vPos;
	m_pTransform->Get_Info(INFO_POS, &vPos);
	if (nullptr == m_pFloor) return;
	m_pFloor->m_pTransform->Set_Pos(vPos);
}

void CRoom::PlaceSubSet()	
{
	const _float colliderThick = 4.f;

	// 벽 위치 조정
	_vec3 vPos;
	float fLengthX = (m_fVtxCntX - 1) * m_fVtxItv;
	float fLengthZ = (m_fVtxCntZ - 1) * m_fVtxItv;
	float fLengthY = VTXITV;

	m_pTransform->Get_Info(INFO_POS, &vPos);
	if (nullptr == m_apWall[0]) return;
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
	_int iTileSize = m_vecTile.size();
	_int iObjSize = m_vecGameObj.size();

	// 룸의 변수 저장
	WriteFile(hFile, &m_fVtxCntX, sizeof(_float), &dwByte, nullptr);
	WriteFile(hFile, &m_fVtxCntZ, sizeof(_float), &dwByte, nullptr);
	WriteFile(hFile, &m_fVtxItv, sizeof(_float), &dwByte, nullptr);
	_int iDoorType = (_int)m_eDoorType;
	WriteFile(hFile, &iDoorType, sizeof(_int), &dwByte, nullptr);
	m_pTransform->WriteTransformFile(hFile, dwByte);
	
	// 타일 컨테이너 저장
	WriteFile(hFile, &iTileSize, sizeof(_int), &dwByte, nullptr);
	for (_int i = 0; i < iTileSize; ++i)
	{
		m_vecTile[i]->m_pTransform->WriteTransformFile(hFile, dwByte);
		dynamic_cast<CTile*>(m_vecTile[i])->WriteTextureName(hFile, dwByte);
	}
		
	
	// 객체 컨테이너 저장
	WriteFile(hFile, &iObjSize, sizeof(_int), &dwByte, nullptr);
	for (_int i = 0; i < iObjSize; ++i)
	{
		// 어떤 객체인지 번호로 저장.
		_int iObjNumber = 0;
		if (dynamic_cast<CBaller*>(m_vecGameObj[i]))
		{
			iObjNumber = 1;
		}
		else if (dynamic_cast<CBub*>(m_vecGameObj[i]))
		{
			iObjNumber = 2;
		}
		else if (dynamic_cast<CGuppi*>(m_vecGameObj[i]))
		{
			iObjNumber = 3;
		}
		else if (dynamic_cast<CTurret*>(m_vecGameObj[i]))
		{
			iObjNumber = 4;
		}
		else if (dynamic_cast<CWalker*>(m_vecGameObj[i]))
		{
			iObjNumber = 5;
		}

		// 세이브 시 어떤 객체인지 정보를 알 수 없을 때 에러메시지 발생.
		if (0 == iObjNumber)
		{
			FAILED_CHECK_RETURN(E_FAIL, false);
		}
		else
		{
			WriteFile(hFile, &iObjNumber, sizeof(_int), &dwByte, nullptr);
			m_vecGameObj[i]->m_pTransform->WriteTransformFile(hFile, dwByte);
		}
	}


	return true;
}

_bool CRoom::ReadRoomFile(HANDLE hFile, DWORD & dwByte)
{
	// 타일 해제
	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Release<CGameObject*>);
	m_vecTile.clear();

	// 오브젝트 해제
	for_each(m_vecGameObj.begin(), m_vecGameObj.end(), Safe_Release<CGameObject*>);
	m_vecGameObj.clear();

	for (auto iter : m_apDoor)
		Safe_Release(iter.second);

	_int iTileSize;
	_int iObjSize;
	// 룸 변수 로드
	ReadFile(hFile, &m_fVtxCntX, sizeof(_float), &dwByte, nullptr);
	ReadFile(hFile, &m_fVtxCntZ, sizeof(_float), &dwByte, nullptr);
	ReadFile(hFile, &m_fVtxItv, sizeof(_float), &dwByte, nullptr);

	//문 로드
	_int iDoorType;
	ReadFile(hFile, &iDoorType, sizeof(_int), &dwByte, nullptr);

	Set_DoorType((DOOR_TYPE)iDoorType);

	m_pTransform->ReadTransformFile(hFile, dwByte);

	// 타일 로드
	ReadFile(hFile, &iTileSize, sizeof(_int), &dwByte, nullptr);
	for (_int i = 0; i < iTileSize; ++i)
	{
		// 타일 트랜스폼 컴포넌트 정보 로드
		CGameObject* objTmp = CTile::Create(m_pGraphicDev, _vec3{ 0.f, 0.f, 0.f }, L"Floor_Level1_Texture");
		PushBack_Tile(objTmp);

		CTile* tmp = dynamic_cast<CTile*>(objTmp);
		m_vecTile[i]->m_pTransform->ReadTransformFile(hFile, dwByte);
		dynamic_cast<CTile*>(m_vecTile[i])->ReadTextureName(hFile, dwByte);

		// 타일 콜라이더 크기 조절 분기문(더러움주의)
		if (fabs(tmp->NormalVectorFromTile().Degree(_vec3::Up())) < 0.1f
			|| fabs(tmp->NormalVectorFromTile().Degree(-_vec3::Up())) < 0.1f)
			tmp->GetCollider()->Set_BoundingBox({ 10.f, 1.f, 10.f });
		else if(fabs(tmp->NormalVectorFromTile().Degree(_vec3::Right())) < 0.1f
			|| fabs(tmp->NormalVectorFromTile().Degree(-_vec3::Right())) < 0.1f)
			tmp->GetCollider()->Set_BoundingBox({ 1.f, 10.f, 10.f });
		else
			tmp->GetCollider()->Set_BoundingBox({ 10.f, 10.f, 1.f });
	}

	// 객체 로드
	ReadFile(hFile, &iObjSize, sizeof(_int), &dwByte, nullptr);
	for (_int i = 0; i < iObjSize; ++i)
	{
		_int iObjNumber = 0;
		ReadFile(hFile, &iObjNumber, sizeof(_int), &dwByte, nullptr);

		if (1 == iObjNumber)
		{
			PushBack_GameObj(CBaller::Create(m_pGraphicDev, _vec3{}));
		}
		else if (2 == iObjNumber)
		{
			PushBack_GameObj(CBub::Create(m_pGraphicDev, _vec3{}));
		}
		else if (3 == iObjNumber)
		{
			PushBack_GameObj(CGuppi::Create(m_pGraphicDev, _vec3{}));
		}
		else if (4 == iObjNumber)
		{
			PushBack_GameObj(CTurret::Create(m_pGraphicDev, _vec3{}));
		}
		else if (5 == iObjNumber)
		{
			PushBack_GameObj(CWalker::Create(m_pGraphicDev, _vec3{}));
		}
		m_vecGameObj[i]->m_pTransform->ReadTransformFile(hFile, dwByte);
	}
	return true;
}

void CRoom::PushBack_Tile(CGameObject * pTile)
{
	NULL_CHECK(pTile);
	m_vecTile.push_back(pTile);
	
	OBJ_INFO objInfo = pTile->Get_ObjInfo();
	m_vecLayer[objInfo.layerID]->Add_GameObject(objInfo.pObjTag, pTile);

	for (int i = 0; i < objInfo.colNameVec.size(); i++)
	{
		CCollider* pCol = dynamic_cast<CCollider*>(pTile->Get_Component(objInfo.colNameVec[i], ID_ALL));
		NULL_CHECK(pCol);
		m_ColliderList[objInfo.colGroupVec[i]].push_back(pCol);
	}
}

void CRoom::PushBack_GameObj(CGameObject * pObj)
{
	NULL_CHECK(pObj);
	m_vecGameObj.push_back(pObj);
	OBJ_INFO objInfo = pObj->Get_ObjInfo();

	m_vecLayer[objInfo.layerID]->Add_GameObject(objInfo.pObjTag, pObj);

	for (int i = 0; i < objInfo.colNameVec.size(); i++)
	{
		CCollider* pCol = dynamic_cast<CCollider*>(pObj->Get_Component(objInfo.colNameVec[i], ID_ALL));
		NULL_CHECK(pCol);
		m_ColliderList[objInfo.colGroupVec[i]].push_back(pCol);
	}	
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
	FreeSubset();
	__super::Free();
}