#pragma once
#include "Tile.h"
class CSnowTile :
	public CTile
{
private:
	CSnowTile(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSnowTile();
public:
	static CSnowTile* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	CTile* LoadSaveTarget(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};

