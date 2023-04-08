#pragma once
#include "Monster.h"
class CWalker : public CMonster
{
private:
	explicit CWalker(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CWalker();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionEnter(const struct Collision* collsion) override {}
	virtual void OnCollisionStay(const struct Collision* collision) override {}
	virtual void OnCollisionExit(const struct Collision* collision) override {}

public:
	static CWalker*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};

