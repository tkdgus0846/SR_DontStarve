#pragma once

#include "Include.h"
#include "GameObject.h"

class CWall;
class CTile;
class CFloor;
class CDoor;

BEGIN(Engine)
	class CLayer;
	class CCollider;
END

class CRoom : public Engine::CGameObject
{
private:
	explicit CRoom(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CRoom();

public:
	HRESULT Ready_GameObject(const _float& fVtxCntX, const _float& fVtxCntZ, const _float& fVtxItv);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	CFloor* GetFloor() const { return m_pFloor; }
	CWall* GetWallArray(_uint index) const { return m_apWall[index]; }

	// 구조 개편(룸->레이어) 이전에 쓰이던 함수
	//void AddTile(CTile* pTile) { if (nullptr == pTile) return; m_vecTile.push_back(pTile); }
	//void AddGameObject(CGameObject* pGameObject) { if (nullptr == pGameObject) return; m_vecGameObj.push_back(pGameObject); }
	_bool& Cur_Door_State(DOOR_DIR eDir) { return m_apDoor[eDir].first; }
	void Set_DoorType(DOOR_TYPE eType);

private:
	virtual HRESULT Add_Component() override;
	HRESULT CreateSubset();
	void	FreeSubset();
	HRESULT Add_GameObject(LAYERID LayerID, const _tchar* pObjTag, CGameObject* pObj);
	
public:
	void FloorSubSet();
	void PlaceSubSet();
	_bool WriteRoomFile(HANDLE hFile, DWORD& dwByte);
	_bool ReadRoomFile(HANDLE hFile, DWORD& dwByte);
	_int ObjNum() const  { return m_vecGameObj.size(); }
	CGameObject* GetObjByIndex(_int iIndex) const
	{
		if (iIndex < 0 || iIndex >= m_vecGameObj.size()) return nullptr;
		return m_vecGameObj[iIndex];
	}

	_int TileNum() const { return m_vecTile.size(); }
	CGameObject* GetTileByIndex(_int iIndex) const
	{
		if (iIndex < 0 || iIndex >= m_vecTile.size()) return nullptr;
		return m_vecTile[iIndex];
	}

	void PushBack_Tile(CGameObject* pTile);
	void PushBack_GameObj(LAYERID LayerID, const _tchar* pObjTag, CGameObject* pObj, COLGROUP eColgroup);

public:
	vector<CLayer*>* GetLayerVec() { return &m_vecLayer; }
	list<CCollider*>* GetColliderList(_int iIndex) 
	{
		return &m_ColliderList[iIndex];
	}

private:
	_float				m_fVtxCntX;
	_float				m_fVtxCntZ;
	_float				m_fVtxItv;

	// 기존의 구조,
	// push_back직접적으로 쓰지말고 PushBack_시리즈 함수들로 쓰셈.
	vector<CGameObject*>	m_vecTile;		// IMGUI에서 사용중
	vector<CGameObject*> m_vecGameObj;	// IMGUI에서 사용중
	CFloor*				m_pFloor;
	array<CWall*, 4>	m_apWall;
	array<pair<_bool, CDoor*>, 4>	m_apDoor;
	DOOR_TYPE			m_eDoorType;
	
private:
	// 레이어용 컨테이너
	vector<CLayer*> m_vecLayer;
	list<CCollider*> m_ColliderList[COL_STATIC_END];

public:
	static CRoom*		Create(LPDIRECT3DDEVICE9 pGraphicDev, 
	const	_float& fVtxCntX = VTXCNTX, const _float& fVtxCntZ = VTXCNTZ, const _float& fVtxItv = VTXITV);

private:
	virtual void Free(void) override;
};

