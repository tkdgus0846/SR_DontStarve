#pragma once
#include "Behavior.h"
class CDig : public CBehavior
{
private:
	explicit CDig(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CDig(const CDig& rhs);
	virtual ~CDig();

public:
	virtual HRESULT Ready_Behavior() override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override;
	virtual void Render_Component(void) override;

	void Set_Magnifi(const _float& fMag = 1.f) { m_fMagnification = fMag; }

private:
	_float m_fMagnification;

public:
	static CDig* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

