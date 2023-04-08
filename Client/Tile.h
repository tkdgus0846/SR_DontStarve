#pragma once
#include "GameObject.h"


class CTile : public CGameObject
{
protected:
	explicit CTile(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CTile();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

protected:
	virtual void Free(void) override;
};