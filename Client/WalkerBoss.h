#pragma once
#include "Monster.h"

BEGIN(Engine)
class CTexture;
class CRcTex;
END

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
	CTexture* m_pTextureCom;
	CRcTex* m_pShadow;

public:
	static CWalkerBoss*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos);
	
	static CGameObject*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"WalkerBoss"; }

private:
	virtual void Free(void) override;
};

