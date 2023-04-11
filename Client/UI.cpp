#include "UI.h"
#include "Export_Function.h"

CUI::CUI(LPDIRECT3DDEVICE9 pGraphicDev) :
	CGameObject(pGraphicDev)
{

}

CUI::~CUI()
{
}

_int CUI::Update_GameObject(const _float& fTimeDelta)
{
	Add_RenderGroup(RENDER_ALPHA_UI, this);
	return __super::Update_GameObject(fTimeDelta);
}