#pragma once
#include "Item.h"

BEGIN(Engine)

class CRcTex;

END

class CCoinItem :
	public CItem
{
private:
	CCoinItem(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CCoinItem();

public:
	virtual HRESULT Add_Component() override;
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	D3DXMATRIX				matWorld, matView;

public:
	static CCoinItem*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual void OnCollisionEnter(const class Collision* collsion) final;
	void	RandCoin();


private:
	virtual void Free(void) override;
};