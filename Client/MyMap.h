#pragma once
#include "GameObject.h"

BEGIN(Engine)

class CFloorTex;
class CTexture;

END

class CRoom;
class CMyMap : public CGameObject
{
private:
	explicit CMyMap(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CMyMap();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	virtual HRESULT Add_Component() override;
	void Create_Default_Room();

private:
	Engine::CFloorTex*	m_pBufferCom;
	Engine::CTexture*	m_pTextureCom;
	array<CRoom*, 25> m_arrRoom;

public:
	static CMyMap* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;
};

