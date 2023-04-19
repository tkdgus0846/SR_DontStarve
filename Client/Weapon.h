#pragma once
#include "GameObject.h"

class CWeapon : public CGameObject
{
	friend class CSwordWeapon;

protected:
	explicit CWeapon(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CWeapon();

public:
	virtual void	Shot();
	virtual _int	Update_GameObject(const _float& fTimeDelta) override;

	_int	Get_CurBulletNum() const { return m_CurBulletNum; }
	_int	Get_MaxBulletNum() const { return m_MaxBulletNum; }
	_bool	Is_BulletEmpty() const { return (m_CurBulletNum == 0) ? true : false; }
	void	SpendBullet(_int bulletNum = 1)
	{
		m_CurBulletNum -= bulletNum;
		if (m_CurBulletNum < 0)  m_CurBulletNum = 0;
	}
	void	GainBullet(_int bulletNum = 1)
	{
		m_CurBulletNum += bulletNum;
		if (m_CurBulletNum > m_MaxBulletNum) m_CurBulletNum = m_MaxBulletNum;
	}

	void	Set_TacticalScope() { m_bTacticalScope = true; }
	_bool	Get_TacticalScope() { return m_bTacticalScope ; }

private:
	_float	m_fAccTime;
	
	_bool	m_bTacticalScope = false;
	_vec3	m_TacticalDir;

protected:
	_int	m_MaxBulletNum; // ���� �� �ִ� �Ѿ� �ִ뷮
	_int	m_CurBulletNum; // ���� �Ѿ� ��

	_float	m_fCycle;		// ���� �� �� �ִ� �ֱ�
	_bool	m_bShooted;		// ����� true�� ������ָ��.
	_bool	m_bEnableShot;	// true�϶��� Shot()�� �ߵ���.

	class CTransform* m_pOwnerTransform;
	_vec3	m_vOffsetTrans;


protected:
	virtual class CBullet*	Shot_Setting() PURE;
	_bool	CanShot() const { return m_bEnableShot && !Is_BulletEmpty(); }
};

