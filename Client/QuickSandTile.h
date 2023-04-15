#pragma once
#include "Tile.h"
class CQuickSandTile :
	public CTile
{
private:
	CQuickSandTile(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CQuickSandTile();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"QuickSandTile"; }
	CGameObject* LoadSaveTarget(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};

