#pragma once

#include "Include.h"
#include "Tile.h"

class CTileFactory
{
public:
	CTileFactory(LPDIRECT3DDEVICE9 pGraphicDev);
	~CTileFactory();

	CTile* CreateTile(TILE_TYPE eTileType, _vec3 vPos = { 0.f, 0.f, 0.f });

private:
	LPDIRECT3DDEVICE9 m_pGraphicDev;
};

