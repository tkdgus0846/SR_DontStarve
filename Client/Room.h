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
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;
	CFloor* GetFloor() { return m_pFloor; }

private:
	void Update_Subset(const _float& fTimeDelta);
	void LateUpdate_SubSet();
	void Render_SubSet();
	HRESULT CreateSubset();
	void FloorSubSet();
	void PlaceSubSet();

private:
	virtual HRESULT Add_Component() override;

private:
	CFloor*				m_pFloor;
	array<CWall*, 4>	m_apWall;

public:
	static CRoom*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};

