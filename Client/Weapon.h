#pragma once
#include "GameObject.h"

class CWeapon : public CGameObject
{
protected:
	explicit CWeapon(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CWeapon();

public:
	// BulletMgr �� Pop�Լ��� ��ӹ޴� �ڽĸ��� ���ø��� �ٸ��� �����ش�.
	virtual class CBullet*	Shot_Setting() PURE;
	void					Shot();
	virtual _int Update_GameObject(const _float& fTimeDelta) override;

private:
	_float	m_fAccTime;
	
protected:
	_float	m_fCycle;		// ���� �� �� �ִ� �ֱ�
	_bool	m_bShooted;		// ����� true�� ������ָ��.
	_bool	m_bEnableShot;	// true�϶��� Shot()�� �ߵ���.

	class CTransform* m_pOwnerTransform;
	_vec3	m_vOffsetTrans;

protected:
	_bool  CanShot() const { return m_bEnableShot; }
	
};

