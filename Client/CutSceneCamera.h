#pragma once
#include "GameObject.h"

BEGIN(Engine)
class CCamera;
END

class CCutSceneCamera : public CGameObject
{
private:
	explicit CCutSceneCamera(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CCutSceneCamera();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	virtual HRESULT Add_Component() override;
	void CutScene();

private:
	Engine::CCamera*	m_pCamera;
	_float	m_fDegree;
	_bool	m_bIsDone;

public:
	static CCutSceneCamera*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;
};

