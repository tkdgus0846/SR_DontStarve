#pragma once
#include "Monster.h"

BEGIN(Engine)

class CAnimation;

END

class CShopNpc :
	public CMonster
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
	D3DXMATRIX  matWorld, matView;
	virtual void OnCollisionEnter(const class Collision* collsion) final;
	virtual void OnCollisionStay(const class Collision* collision) final;

	CAnimation* Ani;

public:
	static CShopNpc*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};

