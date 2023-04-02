#pragma once
#include "Selector.h"

BEGIN(Engine)

class CAIRoot : public CSelector
{
private:
	explicit CAIRoot(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CAIRoot(const CAIRoot& rhs);
	virtual ~CAIRoot();

public:
	virtual HRESULT Ready_Behavior() override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override;
	virtual void Render_Component(void) override;

public:
	static CAIRoot* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

END