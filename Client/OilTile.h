#pragma once
#include "Tile.h"
class COilTile :
	public CTile
{
private:
	COilTile(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~COilTile();
public:
	static COilTile* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	CTile* LoadSaveTarget(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};

