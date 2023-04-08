#pragma once
#include "UI.h"
class CWeaponType :
	public CUI
{
private:
	CWeaponType(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CWeaponType();

public:
	virtual HRESULT Add_Component() override;
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	void		Set_VeiwMatrix_UI();

private:
	D3DXMATRIX  matWorld, matView;

public:
	static CWeaponType*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};
