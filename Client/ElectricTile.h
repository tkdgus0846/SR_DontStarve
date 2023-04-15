#pragma once
#include "Tile.h"
class CElectricTile :
	public CTile
{
private:
	CElectricTile(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CElectricTile();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"ElectricTile"; }
	CTile* LoadSaveTarget(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};

