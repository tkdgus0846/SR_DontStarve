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

	// �׷��� �Ͽ� �浹�˻��ϰԲ� �������. 
	Engine::Check_Collision(COL_PLAYERBULLET, COL_ENEMY);
	Engine::Check_Collision(COL_ENEMYBULLET, COL_PLAYER);
	Engine::Check_Collision(COL_DETECTION, COL_PLAYER);
	Engine::Check_Collision(COL_TRIGGER, COL_PLAYER);
	Engine::Check_Collision(COL_TENNEL, COL_PLAYER);
	Engine::Check_Collision(COL_ENEMY, COL_PLAYER);
	Engine::Check_Collision(COL_ENEMY, COL_ENEMY);

	Engine::Check_Collision(COL_ENVIRONMENT, COL_ENEMY);
	Engine::Check_Collision(COL_ENVIRONMENT, COL_PLAYER);

	Engine::Check_Collision(COL_ITEM, COL_PLAYER);

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

CGameObject* CManagement::Get_GameObject(LAYERID LayerID, const _tchar * pObjTag)
{
	NULL_CHECK_RETURN(pObjTag, nullptr);

	return m_pScene->Get_GameObject(LayerID, pObjTag);
}

CGameObject * CManagement::Get_Player()
{
	//NULL_CHECK_RETURN_MSG(m_pPlayer, nullptr, L"�÷��̾ ���� �߰��� �� ����.");
	return m_pPlayer;
}

void CManagement::Set_Player(CGameObject* player)
{
	if (m_pPlayer) MessageBox(NULL, L"�̹� �÷��̾ �����Ǿ� ����", L"System Message", MB_OK);
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
