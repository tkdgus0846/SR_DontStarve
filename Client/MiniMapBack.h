#pragma once
#include "UI.h"
#include "Player.h"

BEGIN(Engine)

class CRcTex;
class CTexture;
class CAnimation;
class CVIBuffer;

END

struct MiniMapCheck
{
	_bool		m_bCheck = false;
	_bool		m_bInRange = false;
};

class CMiniMapBack :
	public CUI
{
public:
	explicit CMiniMapBack(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CMiniMapBack();

public:
	virtual HRESULT Add_Component() override;
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	D3DXMATRIX  matWorld, matView;

	CRcTex* m_pRcTex;
	CTexture* m_pTexture;

	array<CComponent*, 3 * 3> m_arrMap;
	array<MiniMapCheck, 3 * 3> m_arrBool;

	_float		m_fPosX = 100.f;
	_float		m_fPosY = 100.f;


public:
	static CMiniMapBack*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};