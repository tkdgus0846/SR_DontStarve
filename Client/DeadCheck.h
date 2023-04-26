#pragma once
#include "Behavior.h"

class CDeadCheck : public CBehavior
{
private:
	explicit CDeadCheck(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CDeadCheck(const CDeadCheck& rhs);
	virtual ~CDeadCheck();

public:
	virtual HRESULT Ready_Behavior() override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override {}
	virtual void Render_Component(void) override {}

public:
	static CDeadCheck* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};
