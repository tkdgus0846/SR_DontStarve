#pragma once
#include "Monster.h"
class CNubBoss : public CMonster
{
private:
	explicit CNubBoss(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CNubBoss();

public:
	virtual HRESULT Ready_GameObject(const _vec3& vPos);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	virtual HRESULT Add_Component() override;

public:
	static CNubBoss*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos);

	static CGameObject*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};

