#include "MyEdit.h"

#include "Monster.h"
#include "Bub.h"
#include "Guppi.h"
#include "Baller.h"
#include "Walker.h"
#include "Turret.h"
#include "SkyBox.h"
#include "ObjCamera.h"
#include "EditCamera.h"
#include "Room.h"
#include "MyMap.h"
#include "ImManager.h"
#include "Export_Function.h"

CMyEdit::CMyEdit(LPDIRECT3DDEVICE9 pGraphicDev)
	:CScene(pGraphicDev)
{
}

CMyEdit::~CMyEdit()
{
}

HRESULT CMyEdit::Ready_Scene(void)
{
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Camera", CCamera::Create(m_pGraphicDev)), E_FAIL);

	//Add_GameObject(LAYER_ENVIRONMENT, L"Room", CRoom::Create(m_pGraphicDev));
	Add_GameObject(LAYER_ENVIRONMENT, L"Map", CMyMap::Create(m_pGraphicDev));
	Add_GameObject(LAYER_ENVIRONMENT, L"SkyBox", CSkyBox::Create(m_pGraphicDev));

	Add_GameObject(LAYER_CAMERA, L"Edit_Camera", CEditCamera::Create(m_pGraphicDev));
	Engine::On_Camera(L"Edit_Camera");

	D3DLIGHT9		tLightInfo;
	ZeroMemory(&tLightInfo, sizeof(D3DLIGHT9));

	tLightInfo.Type = D3DLIGHT_DIRECTIONAL;
	tLightInfo.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tLightInfo.Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tLightInfo.Ambient = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tLightInfo.Direction = _vec3(1.f, -1.f, 1.f);

	FAILED_CHECK_RETURN(Engine::Ready_Light(m_pGraphicDev, &tLightInfo, 0), E_FAIL);

	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);

	return S_OK;
}

_int CMyEdit::Update_Scene(const _float & fTimeDelta)
{
	return __super::Update_Scene(fTimeDelta);
}

void CMyEdit::LateUpdate_Scene(void)
{
	__super::LateUpdate_Scene();
}

void CMyEdit::Render_Scene(void)
{

}

CMyEdit * CMyEdit::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMyEdit *	pInstance = new CMyEdit(pGraphicDev);

	if (FAILED(pInstance->Ready_Scene()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CMyEdit::Free(void)
{
	__super::Free();
}
