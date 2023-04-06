#include "stdafx.h"
#include "Logo.h"

#include "Export_Function.h"
#include "BackGround.h"
#include "Stage.h"
#include "MyEdit.h"

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

	Add_GameObject(LAYER_ENVIRONMENT, L"BackGround", CBackGround::Create(m_pGraphicDev));

	m_pLoading = CLoading::Create(m_pGraphicDev, LOADING_STAGE);
	NULL_CHECK_RETURN(m_pLoading, E_FAIL);

	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);

	return S_OK;
}

_int CLogo::Update_Scene(const _float & fTimeDelta)
{
	int iExit = __super::Update_Scene(fTimeDelta);

	if (true == m_pLoading->Get_Finish())
	{
		if (Engine::Key_Down(VK_RETURN))
		{
			CScene*	pScene = CStage::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pScene, -1);

			FAILED_CHECK_RETURN(Engine::Set_Scene(pScene), E_FAIL);

			return 0;
		}

		if (Engine::Key_Pressing(DIK_LCONTROL) && Engine::Key_Down(DIK_RETURN))
		{
			CScene*	pScene = CMyEdit::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pScene, -1);

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

	Engine::Render_Font(L"Font_Default", m_pLoading->Get_String(), &_vec2(20.f, 20.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

}

HRESULT CLogo::Ready_Proto(void)
{
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"RcTex", CRcTex::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Logo_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture/Logo/IU.jpg")), E_FAIL);
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