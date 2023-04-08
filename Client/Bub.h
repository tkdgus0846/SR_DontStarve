#pragma once
#include "Monster.h"

class CBub : public CMonster
{
private:
	explicit CBub(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CBub();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	virtual HRESULT Add_Component() override;
	

public:
	static CBub*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};

