#include "TileFactory.h"
#include "Export_Function.h"

#include "BeltTile.h"
#include "BloodTile.h"
#include "ElectricTile.h"
#include "GrassTile.h"
#include "IceTile.h"
#include "LavaTile.h"
#include "OilTile.h"
#include "QuickSandTile.h"
#include "SandTile.h"
#include "SnowTile.h"
#include "SwampTile.h"

IMPLEMENT_SINGLETON(CLoader)

CLoader::CLoader()
{
	
}

CLoader::~CLoader()
{
	Release();
}

void CLoader::Ready_Loader(LPDIRECT3DDEVICE9 pGraphicDev)
{
	m_pGraphicDev = pGraphicDev;
	pGraphicDev->AddRef();

	ISaveTarget* pTmp = nullptr;

	Insert_SaveTarget(dynamic_cast<CGameObject*>(pTmp)->Get_ObjTag(), pTmp = CBeltTile::Create(pGraphicDev));
	Insert_SaveTarget(dynamic_cast<CGameObject*>(pTmp)->Get_ObjTag(), pTmp = CBloodTile::Create(pGraphicDev));
	Insert_SaveTarget(dynamic_cast<CGameObject*>(pTmp)->Get_ObjTag(), pTmp = CElectricTile::Create(pGraphicDev));
	Insert_SaveTarget(dynamic_cast<CGameObject*>(pTmp)->Get_ObjTag(), pTmp = CGrassTile::Create(pGraphicDev));
	Insert_SaveTarget(dynamic_cast<CGameObject*>(pTmp)->Get_ObjTag(), pTmp = CIceTile::Create(pGraphicDev));
	Insert_SaveTarget(dynamic_cast<CGameObject*>(pTmp)->Get_ObjTag(), pTmp = CLavaTile::Create(pGraphicDev));
	Insert_SaveTarget(dynamic_cast<CGameObject*>(pTmp)->Get_ObjTag(), pTmp = COilTile::Create(pGraphicDev));
	Insert_SaveTarget(dynamic_cast<CGameObject*>(pTmp)->Get_ObjTag(), pTmp = CQuickSandTile::Create(pGraphicDev));
	Insert_SaveTarget(dynamic_cast<CGameObject*>(pTmp)->Get_ObjTag(), pTmp = CSandTile::Create(pGraphicDev));
	Insert_SaveTarget(dynamic_cast<CGameObject*>(pTmp)->Get_ObjTag(), pTmp = CSnowTile::Create(pGraphicDev));
	Insert_SaveTarget(dynamic_cast<CGameObject*>(pTmp)->Get_ObjTag(), pTmp = CSwampTile::Create(pGraphicDev));
}

void CLoader::Release()
{
	for_each(m_mapSaveTarget.begin(), m_mapSaveTarget.end(), CDeleteMap());
	//m_pGraphicDev->Release();
}

CGameObject * CLoader::Load(HANDLE hFile, DWORD& dwByte, const _tchar* tag)
{
	ISaveTarget* pSaveTarget = Find_SaveTarget(tag);

	if (pSaveTarget == nullptr)
		return nullptr;

	CGameObject* pObj = pSaveTarget->PureCreate(m_pGraphicDev);
	pObj->Load(hFile, dwByte);
	return;
}

HRESULT CLoader::Insert_SaveTarget(const _tchar * pTileTag, ISaveTarget * pTile)
{
	if (Find_SaveTarget(pTileTag))
		return E_FAIL;

	m_mapSaveTarget.emplace(pTileTag, pTile);
	return S_OK;
}

ISaveTarget * CLoader::Find_SaveTarget(const _tchar * pTileTag)
{
	auto	iter = find_if(m_mapSaveTarget.begin(), m_mapSaveTarget.end(), CTag_Finder(pTileTag));

	if (iter == m_mapSaveTarget.end())
		return nullptr;

	return iter->second;
}