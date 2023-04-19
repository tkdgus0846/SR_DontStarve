#include "TileFactory.h"

// 타일헤더 파일 모음
#include "BeltTile.h"
#include "BloodTile.h"
#include "ElectricTile.h"
#include "IceTile.h"
#include "GrassTile.h"
#include "LavaTile.h"
#include "OilTile.h"
#include "QuickSandTile.h"
#include "SandTile.h"
#include "SnowTile.h"
#include "SwampTile.h"

IMPLEMENT_SINGLETON(CTileFactory)

CTileFactory::CTileFactory()
{
}

CTileFactory::~CTileFactory()
{
	Release();
}

HRESULT CTileFactory::Ready_Factory(LPDIRECT3DDEVICE9 pGraphicDev)
{
	HRESULT hResult = __super::Ready_Factory(pGraphicDev);

	Register(CIceTile::Tag(), &CIceTile::Create);
	Register(CGrassTile::Tag(), &CGrassTile::Create);
	Register(CLavaTile::Tag(), &CLavaTile::Create);
	Register(COilTile::Tag(), &COilTile::Create);
	Register(CQuickSandTile::Tag(), &CQuickSandTile::Create);
	Register(CSandTile::Tag(), &CSandTile::Create);
	Register(CSnowTile::Tag(), &CSnowTile::Create);
	Register(CSwampTile::Tag(), &CSwampTile::Create);
	
	ExtractTextureKey();

	return hResult;
}