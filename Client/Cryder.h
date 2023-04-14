#pragma once
#include "Monster.h"

class CCryder : public CMonster
{
private:
	explicit CCryder(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CCryder();

public:
	virtual HRESULT Ready_GameObject(const _vec3& vPos);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	virtual HRESULT Add_Component() override;

public:
	static CCryder*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos);

private:
	virtual void Free(void) override;
};

