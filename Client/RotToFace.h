#pragma once
#include "Behavior.h"
class CRotToFace : public CBehavior
{
private:
	explicit CRotToFace(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CRotToFace(const CRotToFace& rhs);
	virtual ~CRotToFace();
	
public:
	virtual HRESULT Ready_Behavior() override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override;
	virtual void Render_Component(void) override;

public:
	static CRotToFace* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

