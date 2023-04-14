#pragma once

#include "Include.h"
#include "GameObject.h"

class CFloor : public Engine::CGameObject
{
private:
	explicit CFloor(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CFloor();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	virtual void OnCollisionEnter(const class Collision* collsion);
	virtual void OnCollisionStay(const class Collision* collision);
	virtual void OnCollisionExit(const class Collision* collision);
private:
	virtual HRESULT Add_Component() override;

public:
	static CFloor*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};

