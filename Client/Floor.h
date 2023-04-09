#pragma once

#include "Include.h"
#include "GameObject.h"

BEGIN(Engine)

class CFloorTex;
class CTransform;
class CTexture;

END
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

private:
	virtual HRESULT Add_Component() override;
	void		Key_Input(const _float& fTimeDelta);

public:
	static CFloor*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};

