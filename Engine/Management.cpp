#include "stdafx.h"
#include "Export_Utility.h"
#include "Layer.h"
#include "Scene.h"


IMPLEMENT_SINGLETON(CManagement)

CManagement::CManagement() :
	m_pPlayer(nullptr),
	m_fWorldTime(0.f),
	m_bPlayingWorldTimer(false)
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

	if (m_bPlayingWorldTimer)
	{
		m_fWorldTime += fTimeDelta;
	}
	
	return m_pScene->Update_Scene(fTimeDelta);
}

void CManagement::LateUpdate_Management()
{
	NULL_CHECK(m_pScene);
	m_pScene->LateUpdate_Scene();

	// 총알과 객체들의 관계
	Engine::Check_Collision(COL_PLAYERBULLET, COL_ENEMY);
	Engine::Check_Collision(COL_PLAYERBULLET, COL_DETECTION);
	Engine::Check_Collision(COL_PLAYERBULLET, COL_ENVIRONMENT);
	Engine::Check_Collision(COL_PLAYERBULLET, COL_OBJ);
	Engine::Check_Collision(COL_ENEMYBULLET, COL_PLAYER);
	
	// 플레이어와 다른 객체들의 관계
	Engine::Check_Collision(COL_PLAYER, COL_OBJ);
	Engine::Check_Collision(COL_PLAYER, COL_ITEM);
	Engine::Check_Collision(COL_PLAYER, COL_TENNEL);
	Engine::Check_Collision(COL_PLAYER, COL_ENEMY);	
	Engine::Check_Collision(COL_PLAYER, COL_DETECTION);
	Engine::Check_Collision(COL_PLAYER, COL_TRIGGER);
	Engine::Check_Collision(COL_PLAYER, COL_ENVIRONMENT);
	Engine::Check_Collision(COL_PLAYER, COL_ROOMITEM);
	/*Engine::Check_Collision(COL_TRIGGER, COL_PLAYERBULLET);*/
	
	// 몬스터와 다른 객체들의 관계
	Engine::Check_Collision(COL_ENEMY, COL_ENEMY);
	Engine::Check_Collision(COL_ENEMY, COL_ENVIRONMENT);
	Engine::Check_Collision(COL_ENEMY, COL_OBJ);
	
	// 기타 등등
	Engine::Check_Collision(COL_OBJ, COL_ENVIRONMENT);
	
	//////////////////////// debug
}

void CManagement::Render_Management(LPDIRECT3DDEVICE9 pGraphicDev)
{
	Engine::Render_GameObject(pGraphicDev);

	NULL_CHECK(m_pScene);
	m_pScene->Render_Scene();
}

void CManagement::Add_GameObject(CGameObject * pObj)
{
	NULL_CHECK(pObj);

	m_pScene->Add_GameObject(pObj);	
}

CGameObject* CManagement::Get_GameObject(LAYERID LayerID, const _tchar * pObjTag)
{
	return m_pScene->Get_GameObject(LayerID, pObjTag);
}

void CManagement::Remove_GameObject(LAYERID layerID, CGameObject* obj)
{
	m_pScene->Remove_GameObject(layerID, obj);
}

CGameObject * CManagement::Get_Player()
{
	//NULL_CHECK_RETURN_MSG(m_pPlayer, nullptr, L"플레이어가 아직 추가된 적 없음.");
	return m_pPlayer;
}

void CManagement::Set_Player(CGameObject* player)
{
	if (m_pPlayer) MessageBox(NULL, L"이미 플레이어가 지정되어 있음", L"System Message", MB_OK);
	m_pPlayer = player;
}

void CManagement::Start_WorldTimer()
{
	m_bPlayingWorldTimer = true;
}

void CManagement::Stop_WorldTimer()
{
	m_bPlayingWorldTimer = false;
}

void CManagement::Free(void)
{
	Safe_Release(m_pScene);
}
