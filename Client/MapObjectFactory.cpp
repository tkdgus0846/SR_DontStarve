#include "MapObjectFactory.h"

#include "HardPyramid.h"
#include "SoftPyramid.h"
#include "Slider.h"

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

	return hResult;
}
