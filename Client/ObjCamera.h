#pragma once
#include "GameObject.h"

BEGIN(Engine)
class CCamera;
END

class CObjCamera : public CGameObject
{
private:
	explicit CObjCamera(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CObjCamera();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	HRESULT		Add_Component(void);
	void		Key_Input(const _float& fTimeDelta);

private:
	Engine::CCamera*	m_pCamera;

public:
	static CObjCamera*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;
};

