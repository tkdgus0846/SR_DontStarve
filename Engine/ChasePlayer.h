#pragma once
#include "Sequence.h"

BEGIN(Engine)

class CBlackBoard;
class CChasePlayer : public CSequence
{
private:
	explicit CChasePlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CChasePlayer(const CChasePlayer& rhs);
	virtual ~CChasePlayer();

public:
	virtual HRESULT Ready_Behavior() override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override;
	virtual void Render_Component(void) override;

public:
	static CChasePlayer* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

END