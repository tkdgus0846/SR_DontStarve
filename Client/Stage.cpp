#include "stdafx.h"
#include "Stage.h"

#include "Export_Function.h"
#include "Monster.h"
#include "Terrain.h"
#include "SkyBox.h"
#include "ObjCamera.h"
#include "Room.h"

CStage::CStage(LPDIRECT3DDEVICE9 pGraphicDev)
	: CScene(pGraphicDev)
{
}

CStage::~CStage()
{
}

HRESULT CStage::Ready_Scene(void)
{
	Add_GameObject(LAYER_ENVIRONMENT, L"Room", CRoom::Create(m_pGraphicDev));
	Add_GameObject(LAYER_ENVIRONMENT, L"SkyBox", CSkyBox::Create(m_pGraphicDev));

	Add_GameObject(LAYER_PLAYER, L"Player", CPlayer::Create(m_pGraphicDev));
	Add_GameObject(LAYER_MONSTER, L"Monster", CMonster::Create(m_pGraphicDev));

	Add_GameObject(LAYER_CAMERA, L"ObjCamera", CObjCamera::Create(m_pGraphicDev));

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

_int CStage::Update_Scene(const _float & fTimeDelta)
{
	return __super::Update_Scene(fTimeDelta);
}

void CStage::LateUpdate_Scene(void)
{
	__super::LateUpdate_Scene();
}

void CStage::Render_Scene(void)
{

}

CStage * CStage::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CStage *	pInstance = new CStage(pGraphicDev);

	if (FAILED(pInstance->Ready_Scene()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CStage::Free(void)
{
	__super::Free();
}
