#pragma once
#include "GameObject.h"

BEGIN(Engine)
class CRoomTex;
class CTexture;

class CRoom : public CGameObject
{
private:
	explicit CRoom(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CRoom();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	HRESULT		Add_Component(void);

private:
	CRoomTex*			m_pBufferCom;
	CTexture*			m_pTextureCom;

public:
	static CRoom*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};

END