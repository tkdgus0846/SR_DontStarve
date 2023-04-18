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
#include "DecoratorTile.h"

#include "FloorGrassS.h"
#include "FloorGrassSE421553.h"
#include "FloorGrassSW.h"
#include "FloorGrassW.h"
#include "FloorGrassW421566.h"
#include "FloorHole421407.h"
#include "FloorHole421573.h"
#include "FloorHole421724.h"
#include "FloorHole421777.h"
#include "FloorSmall.h"
#include "FloorSmall420592.h"
#include "FloorSmall421201.h"
#include "FloorSmall421410.h"
#include "FloorSmall421572.h"
#include "FloorSmall421575.h"
#include "FloorSmall421723.h"
#include "FloorSmall421733.h"

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
	//Register(CDecoratorTile::Tag(), &CDecoratorTile::Create);

	Register(FloorGrassS::Tag(),		FloorGrassS::Create);
	Register(FloorGrassSE421553::Tag(), FloorGrassSE421553::Create);
	Register(FloorGrassSW::Tag(),		FloorGrassSW::Create);
	Register(FloorGrassW::Tag(),		FloorGrassW::Create);
	Register(FloorGrassW421566::Tag(),	FloorGrassW421566::Create);
	Register(FloorHole421407::Tag(),	FloorHole421407::Create);
	Register(FloorHole421573::Tag(),	FloorHole421573::Create);
	Register(FloorHole421724::Tag(),	FloorHole421724::Create);
	Register(FloorHole421777::Tag(),	FloorHole421777::Create);
	Register(FloorSmall::Tag(),			FloorSmall::Create);
	Register(FloorSmall420592::Tag(),	FloorSmall420592::Create);
	Register(FloorSmall421201::Tag(),	FloorSmall421201::Create);
	Register(FloorSmall421410::Tag(),	FloorSmall421410::Create);
	Register(FloorSmall421572::Tag(),	FloorSmall421572::Create);
	Register(FloorSmall421575::Tag(),	FloorSmall421575::Create);
	Register(FloorSmall421723::Tag(),	FloorSmall421723::Create);
	Register(FloorSmall421733::Tag(),	FloorSmall421733::Create);

	ExtractTextureKey();

	return hResult;
}