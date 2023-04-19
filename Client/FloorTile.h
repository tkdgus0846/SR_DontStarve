#pragma once
#include "Tile.h"

class CFloorTile :
	public CTile
{
protected:
	explicit CFloorTile(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CFloorTile();
};