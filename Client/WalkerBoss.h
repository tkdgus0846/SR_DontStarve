#pragma once
#include "Monster.h"
class CWalkerBoss : public CMonster
{
private:
	explicit CWalkerBoss(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CWalkerBoss();

public:
	virtual HRESULT Ready_GameObject(const _vec3& vPos);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	virtual HRESULT Add_Component() override;

public:
	static CWalkerBoss*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos);
	static const _tchar* GetTag() { return L"WalkerBoss"; }
private:
	virtual void Free(void) override;
};

