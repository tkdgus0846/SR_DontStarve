#pragma once

#include "Component.h"

BEGIN(Engine)

class CCamera : public CComponent
{
public:
	enum CAMERA_TYPE { CAM_LAND, CAM_FLY, CAM_END };

private:
	explicit CCamera(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CCamera(const CCamera& rhs);
	virtual ~CCamera();

public:
	HRESULT			Ready_Camera(VIEWPARAMS& tViewParam, PROJPARAMS& tProjParam, HWND& hWnd);
	virtual	_int	Update_Component(const _float& fTimeDelta);
	virtual	void	LateUpdate_Component() {}
	void			Set_LandMode() { m_eType = CAM_LAND; }
	void			Set_FlyMode() { m_eType = CAM_FLY; }

private:
	void		Key_Input(const _float & fTimeDelta);
	void		Mouse_Move();
	void		Fix_Mouse();

	void	Move_Strafe(const _float& fUnits, const _float& fTimeDelta);// Move-Right
	void	Move_Fly(const _float& fUnits, const _float& fTimeDelta);	// Move-Up
	void	Move_Walk(const _float& fUnits, const _float& fTimeDelta);  // Move-Look

	//void	Rot_Pitch(const _float& fAngle, const _float& fTimeDelta);// Rot-Right
	//void	Rot_Yaw(const _float& fAngle, const _float& fTimeDelta);  // Rot-Up
	//void	Rot_Roll(const _float& fAngle, const _float& fTimeDelta); // Rot-Look

private:
	CAMERA_TYPE	m_eType;

	VIEWPARAMS	m_tViewParams;
	PROJPARAMS	m_tProjParams;

	_vec3		m_vLook;
	_float		m_fLength;

	_matrix		m_matView;
	_matrix		m_matProj;

	_bool		m_bFix;
	_bool		m_bClick;

	HWND		m_hWnd;

public:
	static CCamera* Create(LPDIRECT3DDEVICE9 pGraphicDev, 
		VIEWPARAMS& tViewParam = VIEWPARAMS(
	{10.f, 7.f, 29.f},
	{0.f, 0.f, 0.f},
	{ 0.f, 1.f, 0.f }),

		PROJPARAMS& tProjParam = PROJPARAMS(
			D3DXToRadian(60.f),
			(_float)WINCX / WINCY,
			1.f, 1000.f),

		HWND hWnd = g_hWnd);

	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

END