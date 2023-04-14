#pragma once

#include "Component.h"

BEGIN(Engine)

class CCameraMgr;
class CCamera : public CComponent
{
	friend CCameraMgr;

private:
	explicit CCamera(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CCamera(const CCamera& rhs);
	virtual ~CCamera();

public:
	HRESULT			Ready_Camera(VIEWPARAMS& tViewParam, PROJPARAMS& tProjParam);
	virtual	_int	Update_Component(const _float& fTimeDelta);
	virtual	void	LateUpdate_Component() {}

	_matrix*		Get_Camera_ViewMatrix() { return &m_matView; }
	VIEWPARAMS*		Get_Camera_ViewParams() { return &m_tViewParams; }

	void			Set_CameraName(const _tchar* pName) { m_pName = pName; }
	void			Set_ProjParams(PROJPARAMS& tProjParam) { m_tProjParams = tProjParam; }

private:
	void			On_Camera() { m_bSwitch = true; }
	void			Off_Camera() { m_bSwitch = false; }
	void			Shake_Camera() { m_bShack = true; }
	void			Shake(const _float & fTimeDelta, 
							const _float& fForce = 2.f, const _float& fTime = 10.f);

private:
	VIEWPARAMS		m_tViewParams;
	PROJPARAMS		m_tProjParams;

	_matrix			m_matView;
	_matrix			m_matProj;

	const _tchar*	m_pName;
	_bool			m_bSwitch;
	_bool			m_bShack;
	_float			m_fShackForce;
	_float			m_fShackTime;

public:
	static CCamera* Create(LPDIRECT3DDEVICE9 pGraphicDev, 
		VIEWPARAMS& tViewParam = VIEWPARAMS(
			{0.f, 0.f, 0.f},
			{0.f, 0.f, 0.f},
			{ 0.f, 1.f, 0.f }),

		PROJPARAMS& tProjParam = PROJPARAMS(
			D3DXToRadian(60.f),
			(_float)WINCX / WINCY,
			1.0f, 200.f));

	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

END