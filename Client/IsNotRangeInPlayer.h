#pragma once
#include "Behavior.h"

class CIsNotRangeInPlayer : public CBehavior
{
private:
	explicit CIsNotRangeInPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CIsNotRangeInPlayer(const CIsNotRangeInPlayer& rhs);
	virtual ~CIsNotRangeInPlayer();

public:
	virtual HRESULT Ready_Behavior() override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override {}
	virtual void Render_Component(void) override {}

public:
	static CIsNotRangeInPlayer* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

