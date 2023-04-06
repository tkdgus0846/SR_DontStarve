#pragma once
#include "GameObject.h"

BEGIN(Engine)
class CCamera;
END

class CEditCamera : public CGameObject
{
private:
	explicit CEditCamera(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CEditCamera();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	virtual	HRESULT Add_Component() override;
	void	Key_Input(const _float& fTimeDelta);
	void	Mouse_Move(const _float& fTimeDelta);
	void	Fix_Mouse();

private:
	_float				m_fSpeed;
	_bool				m_bFix;
	Engine::CCamera*	m_pCamera;

public:
	static CEditCamera*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;
};

