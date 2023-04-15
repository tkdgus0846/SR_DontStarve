#pragma once
#include "Tile.h"
class CBloodTile :
	public CTile
{
private:
	CBloodTile(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CBloodTile();
public:
	static CBloodTile* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	CTile* LoadSaveTarget(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};

