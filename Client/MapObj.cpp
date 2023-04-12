#include "MapObj.h"
#include "Export_Function.h"

CMapObj::CMapObj(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
	Set_LayerID(LAYER_TRIGGER);
}

CMapObj::~CMapObj()
{
}

void CMapObj::Free(void)
{
}
