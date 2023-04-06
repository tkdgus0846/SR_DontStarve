#pragma once

#include "Include.h"
#include "GameObject.h"
#include "Floor.h"
#include "Wall.h"

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

private:
	virtual HRESULT Add_Component() override;
	void Update_Subset(const _float& fTimeDelta);
	void LateUpdate_SubSet();
	void Render_SubSet();
	HRESULT CreateSubset();

public:
	void FloorSubSet();
	void PlaceSubSet();

private:
	_float				m_fVtxCntX;
	_float				m_fVtxCntZ;
	_float				m_fVtxItv;

private:
	CFloor*				m_pFloor;
	array<CWall*, 4>	m_apWall;

public:
	static CRoom*		Create(LPDIRECT3DDEVICE9 pGraphicDev, 
		const _float& fVtxCntX = VTXCNTX, const _float& fVtxCntZ = VTXCNTZ, const _float& fVtxItv = VTXITV);

private:
	virtual void Free(void) override;
};

