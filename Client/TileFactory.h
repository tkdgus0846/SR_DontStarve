#pragma once
#include "Factory.h"


class CTileFactory :
	public CFactory
{
	DECLARE_SINGLETON(CTileFactory)
private:
	CTileFactory();
	virtual ~CTileFactory();
	
public:
	HRESULT Ready_TileFactory(LPDIRECT3DDEVICE9 pGraphicDev);
	void Release();

};

#define TILE_FACTORY CTileFactory::GetInstance()