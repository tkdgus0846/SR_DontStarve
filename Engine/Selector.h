#pragma once
#include "Behavior.h"

BEGIN(Engine)

class CBlackBoard;
class CSelector : public CBehavior
{
protected:
	explicit CSelector(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSelector(const CSelector& rhs);
	virtual ~CSelector();

public:
	virtual HRESULT Ready_Behavior() PURE;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override;
	virtual void Render_Component(void) override;

public:
	virtual CComponent * Clone(void) PURE;

protected:
	virtual void Free() override;
};

END