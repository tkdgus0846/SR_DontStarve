#pragma once
#include "Weapon.h"
class CSpreaWeapon :
	public CWeapon
{
public:
	explicit CSpreaWeapon(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSpreaWeapon();

public:
	// 발사할 위치. 
	virtual void Shot();
	CBullet*	Shot_Setting() { return nullptr; }
	CBullet*	Shot_Setting(_float fAngle);

	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual HRESULT Add_Component() override;
	virtual HRESULT Ready_GameObject(void) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;


	static CSpreaWeapon*		Create(LPDIRECT3DDEVICE9 pGraphicDev, CTransform* pOnwerTransform);
	virtual void Free(void) override;

private:
	_float		m_fTime = 0.f;
	_bool		m_bShoot = true;
};