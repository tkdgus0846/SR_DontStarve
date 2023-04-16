#pragma once
#include "Monster.h"
class CGuppi : public CMonster
{
private:
	explicit CGuppi(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CGuppi();

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
	static CGuppi*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos);
	static CGameObject*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"Guppi"; }
private:
	virtual void Free(void) override;
};

