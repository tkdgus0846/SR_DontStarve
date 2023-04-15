#pragma once
#include "Tile.h"
class CGrassTile :
	public CTile
{
private:
	CGrassTile(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CGrassTile();
public:
	static CGrassTile* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	CTile* LoadSaveTarget(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};

