#pragma once
#include "GameObject.h"

class CShopNpc :
	public CGameObject
{
public:
	CShopNpc(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CShopNpc();

public:
	virtual HRESULT Add_Component() override;
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	void		Set_ViewMatrix_UI();

private:
	D3DXMATRIX  matWorld, matView;

public:
	static CShopNpc*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};

