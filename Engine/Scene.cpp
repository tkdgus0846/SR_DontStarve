#include "stdafx.h"
#include "Scene.h"

CScene::CScene(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
{
	m_pGraphicDev->AddRef();

	for (int i = 0; i < LAYER_DYNAMIC_END - LAYER_STATIC_END - 1; i++)
	{
		m_DynamicLayerArr[i] = CLayer::Create();
	}
}

CScene::~CScene()
{
}

CComponent * CScene::Get_Component(LAYERID LayerID, const _tchar * pObjTag, const _tchar * pComponentTag, COMPONENTID eID)
{
	return Get_Layer(LayerID)->Get_Component(pObjTag, pComponentTag, eID);
}

HRESULT CScene::Ready_Scene(void)
{
	return S_OK;
}

_int CScene::Update_Scene(const _float & fTimeDelta)
{
	_int iResult = 0;

	for (int i = 0; i < LAYER_DYNAMIC_END; i++)
	{
		iResult = Get_Layer((LAYERID)i)->Update_Layer(fTimeDelta);
		if (iResult & 0x80000000)
			return iResult;
	}
	
	return iResult;
}

void CScene::LateUpdate_Scene(void)
{
	for (int i = 0; i < LAYER_DYNAMIC_END; i++)
	{
		Get_Layer((LAYERID)i)->LateUpdate_Layer();
	}	
}

HRESULT CScene::Add_GameObject(LAYERID LayerID, const _tchar* pObjTag, class CGameObject* pObj)
{
	FAILED_CHECK_RETURN(Get_Layer(LayerID)->Add_GameObject(pObjTag, pObj), E_FAIL);
	return S_OK;
}

CGameObject * CScene::Get_GameObject(LAYERID LayerID, const _tchar * pObjTag)
{
	NULL_CHECK_RETURN(pObjTag);

	return Get_Layer(LayerID)->Get_GameObject(pObjTag);
}

CLayer* CScene::Get_Layer(LAYERID LayerID)
{
	if (LayerID < LAYER_STATIC_END)
	{
		return (*m_StaticLayerArr)[LayerID];
	}
	else if (LayerID < LAYER_DYNAMIC_END)
	{
		return m_DynamicLayerArr[LayerID];
	}
}

void Engine::CScene::Free(void)
{
	for_each(m_DynamicLayerArr.begin(), m_DynamicLayerArr.end(), CDeleteObj());
	Safe_Release(m_pGraphicDev);
}
