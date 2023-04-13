#pragma once
#include "UI.h"

BEGIN(Engine)

class CRcTex;
class CTexture;

END

class CBossHp :
	public CUI
{
	enum BOSSMAP
	{
		BOSS_MAP_GUAGE,
		BOSS_MAP_HP,
		BOSS_MAP_FONT,
		BOSS_MAP_END
	};
	enum BOSSUI
	{
		BOSS_UI_B,
		BOSS_UI_O,
		BOSS_UI_S,
		BOSS_UI_S2,
		BOSS_UI_HP,
		BOSS_UI_GUAGE,
		BOSS_UI_END
	};

private:
	CBossHp(LPDIRECT3DDEVICE9 pGraphicDev);
	~CBossHp();

public:
	virtual HRESULT Add_Component() override;
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	void		Set_ViewMatrix_UI();
	void		Set_ViewMatrix_UI(_float posX, _float posY);
	void		Set_ViewMatrix_UI(_float posX, _float posY, _float scaleX, _float scaleY);

private:
	D3DXMATRIX  matWorld, matView;

	CRcTex* m_sRcTex;
	CRcTex* m_dRcTex;
	array<CComponent*, BOSS_MAP_END> m_arrMap;

	_float m_BOSS1 = 1.f;


public:
	static CBossHp*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};
