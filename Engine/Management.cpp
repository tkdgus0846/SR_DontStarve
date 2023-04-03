#include "stdafx.h"
#include "Export_Utility.h"

IMPLEMENT_SINGLETON(CManagement)

CManagement::CManagement()
{
}

CManagement::~CManagement()
{
	Free();
}

CComponent * CManagement::Get_Component(LAYERID LayerID, const _tchar * pObjTag, const _tchar * pComponentTag, COMPONENTID eID)
{
	NULL_CHECK_RETURN(m_pScene, nullptr);
	return m_pScene->Get_Component(LayerID, pObjTag, pComponentTag, eID);
}

HRESULT CManagement::Set_Scene(CScene * pScene)
{
	Safe_Release(m_pScene);
	Engine::Clear_RenderGroup();

	m_pScene = pScene;

	return S_OK;
}

_int CManagement::Update_Management(const _float & fTimeDelta)
{
	NULL_CHECK_RETURN(m_pScene, -1);
	
	return m_pScene->Update_Scene(fTimeDelta);
}

void CManagement::LateUpdate_Management()
{
	NULL_CHECK(m_pScene);
	m_pScene->LateUpdate_Scene();
	// 충돌체크

	// 그룹끼리만 충돌검사하는 코드 ㅇㅇ 
	//Engine::Check_Collision(COL_ENV, COL_OBJ);
}

void CManagement::Render_Management(LPDIRECT3DDEVICE9 pGraphicDev)
{
	Engine::Render_GameObject(pGraphicDev);

	NULL_CHECK(m_pScene);
	m_pScene->Render_Scene();
}

void CManagement::Add_GameObject(LAYERID LayerID, const _tchar * pObjTag, CGameObject * pObj)
{
	m_pScene->Add_GameObject(LayerID, pObjTag, pObj);
}

CPlayer * CManagement::Get_Player()
{
	return nullptr;
}

void CManagement::Free(void)
{
	Safe_Release(m_pScene);
}
