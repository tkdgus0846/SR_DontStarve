#pragma once
#include "GameObject.h"

class CWeapon : public CGameObject
{
protected:
	explicit CWeapon(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CWeapon();

public:
	// BulletMgr 의 Pop함수를 상속받는 자식마다 템플릿을 다르게 정해준다.
	virtual class CBullet*	Shot_Setting() PURE;
	void					Shot();
	virtual _int Update_GameObject(const _float& fTimeDelta) override;

private:
	_float	m_fAccTime;
	
protected:
	_float	m_fCycle;		// 총을 쏠 수 있는 주기
	_bool	m_bShooted;		// 쏘고나서 true로 만들어주면됨.
	_bool	m_bEnableShot;	// true일때만 Shot()이 발동함.

	class CTransform* m_pOwnerTransform;
	_vec3	m_vOffsetTrans;

protected:
	_bool  CanShot() const { return m_bEnableShot; }
	
};

