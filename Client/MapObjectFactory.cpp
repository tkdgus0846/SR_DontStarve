#include "MapObjectFactory.h"

#include "HardPyramid.h"
#include "SoftPyramid.h"
#include "Slider.h"
#include "TallGrass.h"
#include "Tree.h"
#include "SnowTree.h"
#include "SnowSoTree.h"
#include "SnowMan.h"

IMPLEMENT_SINGLETON(CMapObjectFactory)

CMapObjectFactory::CMapObjectFactory()
{
}


CMapObjectFactory::~CMapObjectFactory()
{
	Release();
}

HRESULT CMapObjectFactory::Ready_Factory(LPDIRECT3DDEVICE9 pGraphicDev)
{
	HRESULT hResult = __super::Ready_Factory(pGraphicDev);

	Register(CHardPyramid::Tag(),	&CHardPyramid::Create);
	Register(CSoftPyramid::Tag(),	&CSoftPyramid::Create);
	Register(CSlider::Tag(),		&CSlider::Create);
	Register(CTallGrass::Tag(),		&CTallGrass::Create);
	Register(CTree::Tag(), &CTree::Create);
	Register(CSnowTree::Tag(), &CSnowTree::Create);
	Register(CSnowSoTree::Tag(), &CSnowSoTree::Create);
	Register(CSnowMan::Tag(), &CSnowMan::Create);

	ExtractTextureKey();

	return hResult;
}
