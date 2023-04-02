#pragma once
#include "Behavior.h"

BEGIN(Engine)

class CBlackBoard;
class CSequence : public CBehavior
{
protected:
	explicit CSequence(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSequence(const CSequence& rhs);
	virtual ~CSequence(); 
	
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