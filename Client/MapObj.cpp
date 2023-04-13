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

void CMapObj::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());

	__super::Render_GameObject();
}