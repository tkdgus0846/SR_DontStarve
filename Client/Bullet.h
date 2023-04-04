#pragma once
#include "GameObject.h"

class CBullet : public CGameObject
{
protected:
	explicit CBullet(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CBullet();

protected:
	// 적 총알인지 우리 총알인지 판단하기 위한 변수
	_bool		m_bIsEnemy;
	// 스피드값.
	_float		m_fSpeed;
	// 살아있을 수 있는 시간
	_float		m_fLifeSpan;
	// 살고 있는 시간
	_float		m_fAge;

public:
	_bool			GetIsEnemy() const { return m_bIsEnemy; }
	void			SetIsEnemy(_bool state) { m_bIsEnemy = state; }
	void			SetAge(_float age = 0.f) { m_fAge = age; }
	_int			Aging(_float fTimeDelta) 
	{ 
		m_fAge += fTimeDelta;
		if (m_fAge >= m_fLifeSpan)
		{
			SetDead();
			return OBJ_RETPOOL;
		}
		return OBJ_NOEVENT;
	}
	virtual void	SetDead() PURE;
	

	
};

