//#include "stdafx.h"
#include "MainApp.h"
#include "Scene.h"
#include "Logo.h"
#include "BulletMgr.h"
#include "EffectManager.h"
#include "ImManager.h"
#include "NogadaFactory.h"
#include <time.h>

#include "Export_Function.h"
#include "RoomMgr.h"
#include "ParticleMgr.h"
#include "TileFactory.h"
#include "FileSystem.h"
#include "SoundMgr.h"

// 주석 테스트용
CMainApp::CMainApp()
	: m_pDeviceClass(nullptr), m_pManagementClass(nullptr), m_pGraphicDev(nullptr)
{
}


CMainApp::~CMainApp()
{
}

HRESULT CMainApp::Ready_MainApp(void)
{
	srand((unsigned int)time(NULL));
	FAILED_CHECK_RETURN(Ready_DefaultSetting(&m_pGraphicDev), E_FAIL);
	FAILED_CHECK_RETURN(Set_Scene(m_pGraphicDev, &m_pManagementClass), E_FAIL);

	SOUND->Init();
	
	PLAY_BGM(L"Title.wav", 1.f);
	return S_OK;
}

int CMainApp::Update_MainApp(const _float & fTimeDelta)
{
	Engine::Update_DInput();
	
	_long	dwMouse = 0;

	if (Engine::Key_Down(DIK_K))
		CFileSystem::Save(L"as.dat");
	if (Engine::Key_Down(DIK_L))
		CFileSystem::Load(L"as.dat");

	m_pManagementClass->Update_Management(fTimeDelta);

	return 0;
}

void CMainApp::LateUpdate_MainApp(void)
{
	m_pManagementClass->LateUpdate_Management();
}

void CMainApp::Render_MainApp(void)
{
	Engine::Render_Begin(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.f));

	m_pManagementClass->Render_Management(m_pGraphicDev);

	Engine::Render_End();
}

HRESULT CMainApp::Ready_DefaultSetting(LPDIRECT3DDEVICE9 * ppGraphicDev)
{
	FAILED_CHECK_RETURN(Engine::Ready_GraphicDev(g_hWnd, MODE_WIN, WINCX, WINCY, &m_pDeviceClass), E_FAIL);
	m_pDeviceClass->AddRef();

	(*ppGraphicDev) = m_pDeviceClass->Get_GraphicDev();
	(*ppGraphicDev)->AddRef();

	

	FAILED_CHECK_RETURN(Engine::Ready_Font((*ppGraphicDev), L"Font_Default", L"바탕", 15, 20, FW_HEAVY), E_FAIL);
	/*FAILED_CHECK_RETURN(Engine::Ready_Font((*ppGraphicDev), L"Font_Jinji", L"궁서", 15, 20, FW_HEAVY), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Font((*ppGraphicDev), L"Font_Ganji", L"견고딕", 15, 20, FW_HEAVY), E_FAIL);*/

	// dinput
	FAILED_CHECK_RETURN(Engine::Ready_DInput(g_hInst, g_hWnd), E_FAIL);

	return S_OK;
}

HRESULT CMainApp::Set_Scene(LPDIRECT3DDEVICE9 pGraphicDev, CManagement ** ppManagement)
{
	CScene*		pScene = nullptr;
	pScene = CLogo::Create(pGraphicDev);
	NULL_CHECK_RETURN(pScene, E_FAIL);

	FAILED_CHECK_RETURN(Engine::Create_Management(ppManagement), E_FAIL);
	(*ppManagement)->AddRef();

	FAILED_CHECK_RETURN((*ppManagement)->Set_Scene(pScene), E_FAIL);

	return S_OK;
}

CMainApp * CMainApp::Create(void)
{
	CMainApp *	pInstance = new CMainApp;

	if (FAILED(pInstance->Ready_MainApp()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	
	return pInstance;
}

void CMainApp::Free(void)
{
	CTileFactory::DestroyInstance();
	//CLoader::DestroyInstance();
	CRoomMgr::DestroyInstance();
	CImManager::DestroyInstance();
	CBulletMgr::DestroyInstance();
	CParticleMgr::DestroyInstance();
	CEffectManager::DestroyInstance();
	CSoundMgr::DestroyInstance();
	

	FreeConsole();
	Safe_Release(m_pGraphicDev);

	Safe_Release(m_pManagementClass);
	Safe_Release(m_pDeviceClass);

	Engine::Release_Utility();
	Engine::Release_System();
}
