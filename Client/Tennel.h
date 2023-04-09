#pragma once
#include "GameObject.h"

BEGIN(Engine)
class CTexture;
END

class CTennel : public CGameObject
{
private:
	explicit CTennel(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CTennel();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	virtual HRESULT Add_Component() override;

private:
	Engine::CTexture*		m_pTextureCom;

public:
	static CTennel*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};

