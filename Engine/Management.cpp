#include "stdafx.h"
#include "Export_Utility.h"


IMPLEMENT_SINGLETON(CManagement)

CManagement::CManagement() :
	m_pPlayer(nullptr)
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

	// 그룹핑 하여 충돌검사하게끔 만들었음. 
	Engine::Check_Collision(COL_PLAYERBULLET, COL_ENEMY);
	Engine::Check_Collision(COL_ENEMYBULLET, COL_PLAYER);
	Engine::Check_Collision(COL_DETECTION, COL_PLAYER);
}

void CManagement::Render_Management(LPDIRECT3DDEVICE9 pGraphicDev)
{
	Engine::Render_GameObject(pGraphicDev);

	NULL_CHECK(m_pScene);
	m_pScene->Render_Scene();
}

void CManagement::Add_GameObject(LAYERID LayerID, const _tchar * pObjTag, CGameObject * pObj)
{
	NULL_CHECK(pObj);

	m_pScene->Add_GameObject(LayerID, pObjTag, pObj);	
}

CGameObject * CManagement::Get_Player()
{
	NULL_CHECK_RETURN_MSG(m_pPlayer, nullptr, L"플레이어가 아직 추가된 적 없음.");
	return m_pPlayer;
}

void CManagement::Set_Player(CGameObject* player)
{
	if (m_pPlayer) MessageBox(NULL, L"이미 플레이어가 지정되어 있음", L"System Message", MB_OK);
	m_pPlayer = player;
}

void CManagement::Free(void)
{
	Safe_Release(m_pScene);
}
