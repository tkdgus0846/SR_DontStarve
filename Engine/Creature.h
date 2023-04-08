#pragma once
#include "GameObject.h"

class CCreature : public CGameObject
{
protected:
	explicit CCreature(LPDIRECT3DDEVICE9 pGrapicDev);
	virtual ~CCreature();

public:
	virtual HRESULT		Ready_GameObject(void);
	virtual _int		Update_GameObject(const _float& fTimeDelta);
	virtual void		LateUpdate_GameObject(void);
	virtual void		Render_GameObject(void);

protected:
	_float	m_fSpeed;
	_int	m_iHp;
	_int	m_iAttack;

protected:
	virtual void Free() override;
};

