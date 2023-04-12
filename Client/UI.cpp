#include "UI.h"
#include "Export_Function.h"

CUI::CUI(LPDIRECT3DDEVICE9 pGraphicDev) :
	CGameObject(pGraphicDev)
{
	Set_LayerID(LAYER_UI);
}

CUI::~CUI()
{
}
