#pragma once
#include "Tile.h"
class CSandTile :
	public CTile
{
private:
	CSandTile(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSandTile();
public:
	static CSandTile* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	CTile* LoadSaveTarget(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};

