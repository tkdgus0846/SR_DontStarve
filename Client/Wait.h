#pragma once
#include "Behavior.h"

class CBlackBoard;
class CWait : public CBehavior
{
private:
	explicit CWait(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CWait(const CWait& rhs);
	virtual ~CWait();

public:
	virtual HRESULT Ready_Behavior() override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override {};
	virtual void Render_Component(void) override {};

public:
	static CWait* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};