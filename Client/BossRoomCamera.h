#pragma once
#include "GameObject.h"

BEGIN(Engine)
class CCamera;
END

class CBossRoomCamera : public CGameObject
{
private:
	explicit CBossRoomCamera(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CBossRoomCamera();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	virtual HRESULT Add_Component() override;

private:
	Engine::CCamera*	m_pCamera;

public:
	static CBossRoomCamera*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;
};

