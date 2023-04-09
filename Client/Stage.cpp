#include "stdafx.h"
#include "Stage.h"

#include "Monster.h"
#include "Bub.h"
#include "Guppi.h"
#include "Baller.h"
#include "Walker.h"
#include "Turret.h"
#include "SkyBox.h"
#include "ObjCamera.h"
#include "Room.h"
#include "MyMap.h"
#include "ImManager.h"
#include "Export_Function.h"
#include "GunUI.h"
#include "BulletBar.h"
#include "BulletGauge.h"
#include "CrossHair.h"
#include "Hp.h"
#include "Coin.h"
#include "Disc.h"
#include "WeaponType.h"
#include "MiniMap.h"

CStage::CStage(LPDIRECT3DDEVICE9 pGraphicDev)
	: CScene(pGraphicDev)
{
}

CStage::~CStage()
{
}

HRESULT CStage::Ready_Scene(void)
{
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Camera", CCamera::Create(m_pGraphicDev)), E_FAIL);
	
	/*Add_GameObject(LAYER_ENVIRONMENT, L"Room", CRoom::Create(m_pGraphicDev));
	dynamic_cast<CRoom*>(Get_GameObject(LAYER_ENVIRONMENT, L"Room"))->FloorSubSet();
	dynamic_cast<CRoom*>(Get_GameObject(LAYER_ENVIRONMENT, L"Room"))->PlaceSubSet();*/
	Add_GameObject(LAYER_ENVIRONMENT, L"Map", CMyMap::Create(m_pGraphicDev));

	Add_GameObject(LAYER_ENVIRONMENT, L"SkyBox", CSkyBox::Create(m_pGraphicDev));
	Add_GameObject(LAYER_PLAYER, L"Player", CPlayer::Create(m_pGraphicDev));

	/*Add_GameObject(LAYER_MONSTER, L"Monster_Baller", CBaller::Create(m_pGraphicDev));
	Add_GameObject(LAYER_MONSTER, L"Monster_Walker", CWalker::Create(m_pGraphicDev));*/
	//Add_GameObject(LAYER_MONSTER, L"Monster_Turret", CTurret::Create(m_pGraphicDev));
	Add_GameObject(LAYER_MONSTER, L"Monster_Bub", CBub::Create(m_pGraphicDev, {1.f, 1.f, 1.f}));
	Add_GameObject(LAYER_MONSTER, L"Monster_Bub", CBub::Create(m_pGraphicDev, {1.f, 1.f, 1.f}));
	Add_GameObject(LAYER_MONSTER, L"Monster_Bub", CBub::Create(m_pGraphicDev, {1.f, 1.f, 1.f}));
	Add_GameObject(LAYER_MONSTER, L"Monster_Bub", CBub::Create(m_pGraphicDev, {1.f, 1.f, 1.f}));
	/*Add_GameObject(LAYER_MONSTER, L"Monster_Guppi_Blue_Texture", CGuppi::Create(m_pGraphicDev));*/

	Add_GameObject(LAYER_CAMERA, L"ObjCamera", CObjCamera::Create(m_pGraphicDev));

	
	
	// UI
	Add_GameObject(LAYER_UI, L"BulletGauge", CBulletGauge::Create(m_pGraphicDev));
	Add_GameObject(LAYER_UI, L"BulletBar", CBulletBar::Create(m_pGraphicDev));
	Add_GameObject(LAYER_UI, L"CrossHair", CCrossHair::Create(m_pGraphicDev));
	Add_GameObject(LAYER_UI, L"Hp", CHp::Create(m_pGraphicDev));
	Add_GameObject(LAYER_UI, L"Coin", CCoin::Create(m_pGraphicDev));
	Add_GameObject(LAYER_UI, L"Disc", CDisc::Create(m_pGraphicDev));
	Add_GameObject(LAYER_UI, L"WeaponType", CWeaponType::Create(m_pGraphicDev));
	Add_GameObject(LAYER_UI, L"MiniMap", CMiniMap::Create(m_pGraphicDev));

	Add_GameObject(LAYER_UI, L"GunUI", CGunUI::Create(m_pGraphicDev));


	/*D3DLIGHT9		tLightInfo;

	ZeroMemory(&tLightInfo, sizeof(D3DLIGHT9));

	tLightInfo.Type = D3DLIGHT_DIRECTIONAL;
	tLightInfo.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tLightInfo.Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tLightInfo.Ambient = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tLightInfo.Direction = _vec3(1.f, 1.f, 1.f);

	FAILED_CHECK_RETURN(Engine::Ready_Light(m_pGraphicDev, &tLightInfo, 0), E_FAIL);*/

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
