#pragma once
#include "Behavior.h"

class CAttack : public CBehavior
{
private:
	explicit CAttack(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CAttack(const CAttack& rhs);
	virtual ~CAttack();

public:
	virtual HRESULT Ready_Behavior() override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override {}
	virtual void Render_Component(void) override;
	
private:
	_float m_fCoolTime;

public:
	static CAttack* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

