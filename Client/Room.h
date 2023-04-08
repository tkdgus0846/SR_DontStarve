#pragma once

#include "Include.h"
#include "GameObject.h"
#include "Floor.h"
#include "Wall.h"
#include "Tile.h"


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
	CFloor* GetFloor() { return m_pFloor; }
	CWall* GetWallArray(_uint index) { return m_apWall[index]; }
	void AddTile(CTile* pTile) { if (nullptr == pTile) return; m_vecTile.push_back(pTile); }
private:
	virtual HRESULT Add_Component() override;
	void Update_Subset(const _float& fTimeDelta);
	void LateUpdate_SubSet();
	void Render_SubSet();
	HRESULT CreateSubset();	

public:
	void FloorSubSet();
	void PlaceSubSet();
	_bool WriteRoomFile(HANDLE hFile, DWORD& dwByte);
	_bool ReadRoomFile(HANDLE hFile, DWORD& dwByte);
	_int ObjNum() { return m_vecGameObj.size(); }
	CGameObject* GetObjByIndex(_int iIndex) 
	{
		if (iIndex < 0 || iIndex >= m_vecGameObj.size()) return nullptr;
		return m_vecGameObj[iIndex];
	}
private:
	_float				m_fVtxCntX;
	_float				m_fVtxCntZ;
	_float				m_fVtxItv;
	vector<CTile*>		m_vecTile;
	vector<CGameObject*> m_vecGameObj;

private:
	CFloor*				m_pFloor;
	array<CWall*, 4>	m_apWall;

public:
	static CRoom*		Create(LPDIRECT3DDEVICE9 pGraphicDev, 
		const _float& fVtxCntX = VTXCNTX, const _float& fVtxCntZ = VTXCNTZ, const _float& fVtxItv = VTXITV);

private:
	virtual void Free(void) override;
};

