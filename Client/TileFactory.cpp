#include "TileFactory.h"

CTileFactory::CTileFactory(LPDIRECT3DDEVICE9 pGraphicDev)
	:m_pGraphicDev(pGraphicDev)
{
	m_pGraphicDev->AddRef();
}

CTileFactory::~CTileFactory()
{
	m_pGraphicDev->Release();
}

CTile * CTileFactory::CreateTile(TILE_TYPE eTileType, _vec3 vPos)
{
	CTile* pTile = nullptr;
	switch (eTileType)
	{
	case TILE_BELT:
		pTile = CTile::Create(m_pGraphicDev, vPos, L"FloorBelt");
		break;
	case TILE_BLOOD:
		pTile= CTile::Create(m_pGraphicDev, vPos, L"FloorBlood");
		break;
	case TILE_ELECTRIC:
		pTile = CTile::Create(m_pGraphicDev, vPos, L"FloorElectric");
		break;
	case TILE_LAVA:
		pTile = CTile::Create(m_pGraphicDev, vPos, L"FloorLava");
		break;
	case TILE_OIL:
		pTile = CTile::Create(m_pGraphicDev, vPos, L"FloorOil");
		break;
	case TILE_QUICKSAND:
		pTile = CTile::Create(m_pGraphicDev, vPos, L"FloorQuicksand");
		break;
	case TILE_SWAMP:
		pTile = CTile::Create(m_pGraphicDev, vPos, L"FloorSwamp");
		break;
	case TILE_ICE:
		//pTile = CTile::Create(m_pGraphicDev, vPos, L"FloorBelt");
		break;
	case TILE_SAND:
		//pTile = CTile::Create(m_pGraphicDev, vPos, L"FloorBelt");
		break;
	case TILE_GRASS:
		//pTile = CTile::Create(m_pGraphicDev, vPos, L"FloorBelt");
		break;
	case TILE_DEFAULT:
		//pTile = CTile::Create(m_pGraphicDev, vPos, L"FloorBelt");
		break;
	case TILE_SNOW:
		//pTile = CTile::Create(m_pGraphicDev, vPos, L"FloorBelt");
		break;
	case TILE_END:
		break;
	default:
		break;
	}
	NULL_CHECK_RETURN(pTile, nullptr);
	return nullptr;
}
