#pragma once
#include "Behavior.h"

class CIsRangeInPlayer : public CBehavior
{
private:
	explicit CIsRangeInPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CIsRangeInPlayer(const CIsRangeInPlayer& rhs);
	virtual ~CIsRangeInPlayer();

public:
	virtual HRESULT Ready_Behavior() override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override {}
	virtual void Render_Component(void) override {}

public:
	static CIsRangeInPlayer* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

