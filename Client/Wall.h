#pragma once

#include "Include.h"
#include "GameObject.h"

BEGIN(Engine)
class CTexture;
END

class CWall : public Engine::CGameObject
{
public:
	explicit CWall(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CWall();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	virtual HRESULT Add_Component() override;

private:
	Engine::CTexture*	m_pTextureCom;

public:
	static CWall*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};