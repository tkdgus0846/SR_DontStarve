#include "stdafx.h"
#include "Scene.h"

CScene::CScene(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
{
	m_pGraphicDev->AddRef();

	for (int i = 0; i < LAYER_END; i++)
	{
		m_arrLayer[i] = CLayer::Create();
	}
}

CScene::~CScene()
{
}

CComponent * CScene::Get_Component(LAYERID LayerID, const _tchar * pObjTag, const _tchar * pComponentTag, COMPONENTID eID)
{
	return m_arrLayer[LayerID]->Get_Component(pObjTag, pComponentTag, eID);
}

HRESULT CScene::Ready_Scene(void)
{
	return S_OK;
}

_int CScene::Update_Scene(const _float & fTimeDelta)
{
	_int iResult = 0;

	for (CLayer* iter : m_arrLayer)
	{
		iResult = iter->Update_Layer(fTimeDelta);

		if (iResult & 0x80000000)
			return iResult;
	}

	return iResult;
}

void CScene::LateUpdate_Scene(void)
{
	for (CLayer* iter : m_arrLayer)
		iter->LateUpdate_Layer();
}

HRESULT CScene::Add_GameObject(LAYERID LayerID, const _tchar* pObjTag, class CGameObject* pObj)
{
	FAILED_CHECK_RETURN(m_arrLayer[LayerID]->Add_GameObject(pObjTag, pObj), E_FAIL);
	return S_OK;
}

void Engine::CScene::Free(void)
{
	for_each(m_arrLayer.begin(), m_arrLayer.end(), CDeleteObj());	
	Safe_Release(m_pGraphicDev);
}
