#pragma once
#include "UI.h"
#include "Player.h"
BEGIN(Engine)

class CRcTex;
class CTexture;
class CAnimation;

END

class CMiniMap :
	public CUI
{
private:
	CMiniMap(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CMiniMap();

public:
	virtual HRESULT Add_Component() override;
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	void		Set_VeiwMatrix_UI();

private:
	D3DXMATRIX  matWorld, matView;

public:
	static CMiniMap*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};

