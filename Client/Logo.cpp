#include "Logo.h"

#include "Export_Function.h"
#include "BackGround.h"
#include "Stage.h"
#include "MyEdit.h"
#include "FileSystem.h"
#include "RoomMgr.h"
#include "Loading.h"
#include "..\Engine\SoundMgr.h"

#include "TileFactory.h"
#include "MonsterFactory.h"
#include "MapObjectFactory.h"


CLogo::CLogo(LPDIRECT3DDEVICE9 pGraphicDev)
	: CScene(pGraphicDev), m_pLoading(nullptr)
{
}

CLogo::~CLogo()
{
}

HRESULT CLogo::Ready_Scene(void)
{
	FAILED_CHECK_RETURN(Ready_Proto(), E_FAIL);

	m_pBackGround = CBackGround::Create(m_pGraphicDev);
	Add_GameObject(m_pBackGround);

	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);

	m_bLoadingCreated = false;

	//STOP_ALL_SOUND;
	//PLAY_BGM(L"Title.wav", SOUND_BGM, 0.5f);

	/*m_pLoading = CLoading::Create(m_pGraphicDev, LOADING_STAGE);
	NULL_CHECK_RETURN(m_pLoading, E_FAIL);*/
	
	return S_OK;
}

_int CLogo::Update_Scene(const _float & fTimeDelta)
{
	int iExit = __super::Update_Scene(fTimeDelta);

	if (m_pBackGround->Get_GameMode() == GAMEMODE_NOCHOICE) return 0;
	if (m_pBackGround->Get_GameMode() == GAMEMODE_EXITGAME)
	{
		DestroyWindow(g_hWnd);
		return -1;
	}

	if (m_pBackGround->Selected_GameMode() && m_bLoadingCreated == false)
	{
		m_pLoading = CLoading::Create(m_pGraphicDev, LOADING_STAGE);
		NULL_CHECK_RETURN(m_pLoading, -1);
		m_bLoadingCreated = true;
	}

	if (true == m_pLoading->Get_Finish())
	{
		if (m_pBackGround->Get_GameMode() == GAMEMODE_EDITOR)
		{
			CScene*	pScene = CMyEdit::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pScene, -1);

			pScene->Set_StaticLayerArr(ROOM_MGR->Get_CurLayerVec());

			for (int i = 0; i < COL_STATIC_END; i++)
			{
				CCollisionMgr::GetInstance()->Set_StaticColliderList(ROOM_MGR->Get_CurColliderList(i), i);
			}

			FAILED_CHECK_RETURN(Engine::Set_Scene(pScene), E_FAIL);
			pScene->Update_Scene(fTimeDelta);
			return 0;
		}

		if (m_pBackGround->Get_GameMode() == GAMEMODE_STARTGAME)
		{
			Start_WorldTimer();
			CScene*	pScene = CStage::Create(m_pGraphicDev);
			
			NULL_CHECK_RETURN(pScene, -1);

			pScene->Set_StaticLayerArr(ROOM_MGR->Get_CurLayerVec());
			
			for (int i = 0; i < COL_STATIC_END; i++)
			{
				CCollisionMgr::GetInstance()->Set_StaticColliderList(ROOM_MGR->Get_CurColliderList(i), i);
			}
			
			FAILED_CHECK_RETURN(Engine::Set_Scene(pScene), E_FAIL);		
			return 0;
		}
	}

	return iExit;
}

void CLogo::LateUpdate_Scene(void)
{
	__super::LateUpdate_Scene();
}

void CLogo::Render_Scene(void)
{
	// _DEBUG �� ���	
	if (m_pLoading == nullptr) return;

	Engine::Render_Font(L"Font_Default", m_pLoading->Get_String(), &_vec2(20.f, 20.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

}

HRESULT CLogo::Ready_Proto(void)
{
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"RcTex", CRcTex::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Logo_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Logo/title3D.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Background_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Logo/BackGround.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"StarBullet_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Star_%d.png",4)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"SelectArrow_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/GUI/SelectArrow.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Num_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Text/tigl_font2_DEPRECATE_%d.png", 42)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Animation", CAnimation::Create(m_pGraphicDev)), E_FAIL);


	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Transform", CTransform::Create(m_pGraphicDev)), E_FAIL);

	return S_OK;
}

CLogo * CLogo::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLogo *	pInstance = new CLogo(pGraphicDev);

	if (FAILED(pInstance->Ready_Scene()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CLogo::Free(void)
{
	Safe_Release(m_pLoading);
	__super::Free();
}