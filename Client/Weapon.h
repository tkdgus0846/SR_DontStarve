#pragma once
#include "GameObject.h"

class CWeapon : public CGameObject
{
protected:
	explicit CWeapon(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CWeapon();

public:
	// BulletMgr �� Pop�Լ��� ��ӹ޴� �ڽĸ��� ���ø��� �ٸ��� �����ش�.
	virtual void Shot() PURE;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;

	_vec3	m_vShotPoint;

private:
	_float	m_fAccTime;		// 
	_bool	m_bEnableShot;	// true�϶��� Shot()�� �ߵ���.

protected:
	_int	m_iDamage;		// ������
	_float	m_fCycle;		// ���� �� �� �ִ� �ֱ�
	_bool	m_bShooted;		// ����� true�� ������ָ��.

	class CTransform* m_pOwnerTransform;
	_vec3	m_vOffsetTrans;

protected:
	_bool  CanShot() const { return m_bEnableShot; }
};

