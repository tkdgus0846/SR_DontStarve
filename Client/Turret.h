#pragma once
#include "Monster.h"

class CTurret : public CMonster
{
private:
	explicit CTurret(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CTurret();

public:
	virtual HRESULT Ready_GameObject(const _vec3& vPos);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionEnter(const struct Collision* collsion) override {}
	virtual void OnCollisionStay(const struct Collision* collision) override {}
	virtual void OnCollisionExit(const struct Collision* collision) override {}

public:
	static CTurret*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos);
	static CGameObject*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};

