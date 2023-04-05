#pragma once
#include "Behavior.h"
class CLeapJump : public CBehavior
{
private:
	explicit CLeapJump(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CLeapJump(const CLeapJump& rhs);
	virtual ~CLeapJump();

public:
	virtual HRESULT Ready_Behavior() override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override {}
	virtual void Render_Component(void) override;

private:
	_float m_fTime;
	_float m_fInit;

public:
	static CLeapJump* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

