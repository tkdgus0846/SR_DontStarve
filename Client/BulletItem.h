#pragma once
#include "Item.h"

BEGIN(Engine)

class CRcTex;

END

class CBulletItem :
	public CItem
{
private:
	CBulletItem(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CBulletItem();

public:
	virtual HRESULT Add_Component() override;
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	D3DXMATRIX				matWorld, matView;

public:
	static CBulletItem*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual void OnCollisionEnter(const class Collision* collsion) final;
	virtual void OnCollisionStay(const class Collision* collision) final;

private:
	virtual void Free(void) override;
};