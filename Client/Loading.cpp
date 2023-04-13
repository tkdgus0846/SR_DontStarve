#include "stdafx.h"
#include "Loading.h"

#include "Export_Function.h"
#include "MonoBehaviors.h"

#include "RoomMgr.h"

CLoading::CLoading(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
	, m_bFinish(false)
{
	ZeroMemory(m_szString, sizeof(_tchar) * 128);
	m_pGraphicDev->AddRef();
}

CLoading::~CLoading()
{
}

unsigned int CLoading::Thread_Main(void * pArg)
{
	CLoading*	pLoading = reinterpret_cast<CLoading*>(pArg);

	_uint iFlag = 0;

	EnterCriticalSection(&(pLoading->Get_Crt()));

	switch (pLoading->Get_LoadingID())
	{
	case LOADING_STAGE:
		iFlag = pLoading->Loading_ForStage();
		break;
	
	case LOADING_BOSS:
		break;
	}
	
	LeaveCriticalSection(&(pLoading->Get_Crt()));

	//_endthreadex(0);

	if (iFlag == E_FAIL)
		exit(-1);

	return iFlag;
}

HRESULT CLoading::Ready_Loading(LOADINGID eID)
{
	InitializeCriticalSection(&m_Crt);

	// 1. 보안 속성
	// 2. 스택 메모리의 크기, 0인 경우 쓰레드가 요구하는 크기만큼 할당
	// 3. 쓰레드 함수의 이름(함수 포인터)
	// 4. 쓰레드 함수를 통해 가공하고자 하는 데이터의 주소
	// 5. 쓰레드의 생성 및 실행을 조절하기 위한 FLAG 값, 기본 값으로 0
	// 6. 쓰레드 ID반환
	
	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, Thread_Main, this, 0, nullptr);

	m_eID = eID;

	// 빨간색으로 블랜딩할 멀티 텍스처 용도의 텍스처 파일
	IDirect3DBaseTexture9*			redTexture;
	FAILED_CHECK_RETURN(D3DXCreateTextureFromFile(m_pGraphicDev, L"../Resource/CollisionDebug/Red.png", (LPDIRECT3DTEXTURE9*)&redTexture), E_FAIL);
	m_pGraphicDev->SetTexture(1, redTexture);

	return S_OK;
}

_uint CLoading::Loading_ForStage(void)
{
	Set_String(L"Texture Loading....");

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Player_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture/Player/Sonic.png")), E_FAIL);

	// Bullet Texture
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"NormalBullet_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Bullet/bigbullet_%d.png", 2)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"IceBullet_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Bullet/iceBeam_%d.png", 4)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FireBullet_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Effect/smallExplode_%d.png", 4)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"VortexBulletBefore_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Effect/Energy_%d.png", 8)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"VortexBulletAfter_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Bullet/vortex.png")), E_FAIL);

	// Monster Texture
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_Bub_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Enemy/bub_%d.png", 2)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_Guppi_Blue_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Enemy/guppi_blue_%d.png", 4)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_Guppi_Green_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Enemy/guppi_green_%d.png", 4)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_Baller_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Enemy/baller_%d.png", 14)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_Walker_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Enemy/walker_%d.png", 4)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_Turret_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Enemy/sprTurret_strip8_0.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"ExplosionBlue", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Effect/ExplosionBlue_%d.png",5)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"RedBlood", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Effect/redblood_%d.png", 4)), E_FAIL);

	//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_Guppi_Green_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Enemy/guppi_green_%d.png", 4)), E_FAIL);
	//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_Guppi_Green_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Enemy/guppi_green_%d.png", 4)), E_FAIL);
	//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_Guppi_Green_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Enemy/guppi_green_%d.png", 4)), E_FAIL);
	//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_Guppi_Green_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Enemy/guppi_green_%d.png", 4)), E_FAIL);
	//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_Guppi_Green_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Enemy/guppi_green_%d.png", 4)), E_FAIL);

	// Collision Texture for the Debug
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Collision_Green_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/CollisionDebug/Green.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Collision_Red_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/CollisionDebug/Red.png")), E_FAIL);

	// Tile Texture
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Floor_Level1_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorLarge #421865.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Wall_Level1_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/WallPanels.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Floor_Level2_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorLarge #421874.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Wall_Level2_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/WallPanels #420377.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorCrate_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Level/Floor/FloorCrate.png")), E_FAIL);


	/*이거 바꾸셈!!!*/FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Dock_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Level/dock_14.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Gun", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Gun/Gun.png")), E_FAIL);

	// Map Object
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"SoftPyramid_Texture", CTexture::Create(m_pGraphicDev, TEX_CUBE, L"../Resource/Texture2D/Entities/SoftPyramid.dds")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"HardPyramid_Texture", CTexture::Create(m_pGraphicDev, TEX_CUBE, L"../Resource/Texture2D/Entities/HardPyramid.dds")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Slider_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/slider.png")), E_FAIL);

	// UI
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"BulletBar_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Gui/hud_secondary_ext_edit.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"BulletGauge_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Gui/hud_ammo_3.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"CrossHair_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Gui/sprReticle_%d.png", 4)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Hp_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Gui/hud_hearts_%d.png", 5)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Coin_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Gui/sprBigCoin_strip6_%d.png", 6)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Disc_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Gui/data_%d.png", 4)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Num_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Text/tigl_font2_DEPRECATE_%d.png", 42)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Weapon_bigshot_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Gui/Weapon_bigshot.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Weapon_explosiveshot_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Gui/Weapon_explosiveshot.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Weapon_flameshot_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Gui/Weapon_flameshot.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Weapon_rapidshot_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Gui/Weapon_rapidshot.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Weapon_spreadshot_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Gui/Weapon_spreadshot.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Weapon_freezeshot_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Gui/Weapon_freezeshot.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Weapon_lasershot_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Gui/Weapon_lasershot.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"MiniMap_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Gui/hud_map.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"MapPos_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Gui/Map/mapPos.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"ESWN_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Gui/Map/ESWN.png")), E_FAIL);
	
	// Item
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"SmallCoin_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Item/sprCoin_strip6_%d.png", 6)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"BulletItem_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Item/sprBullet_%d.png", 2)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"HeartItem_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Sprite/Item/hearts_0.png")), E_FAIL);
	
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"SkyBox_Texture", CTexture::Create(m_pGraphicDev, TEX_CUBE, L"../Resource/Texture2D/SkyBox/SkyBox.dds")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Level1_Tennel_Texture", CTexture::Create(m_pGraphicDev, TEX_CUBE, L"../Resource/Texture2D/Level/Level1_Tennel.dds")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Level2_Tennel_Texture", CTexture::Create(m_pGraphicDev, TEX_CUBE, L"../Resource/Texture2D/Level/Level2_Tennel.dds")), E_FAIL);

	Set_String(L"Buffer Loading.......");

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"TriCol", CTriCol::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"RcCol", CRcCol::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"CubeTex", CCubeTex::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"RcTex_Dynamic", CRcTex::Create(m_pGraphicDev, VB_DYNAMIC)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"RoomTex", CRoomTex::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FloorTex", CFloorTex::Create(m_pGraphicDev, VTXCNTX, VTXCNTZ, VTXITV)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"MapTex", CFloorTex::Create(m_pGraphicDev, 5, 5, 60)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"WallTex", CWallTex::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FrustrumNormalTex", CFrustrumNormalTex::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Collider", CCollider::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"RigidBody", CRigidbody::Create(m_pGraphicDev)), E_FAIL);
	
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Animation", CAnimation::Create(m_pGraphicDev)), E_FAIL);
	
	/////////////////////////// 파티클
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Snow_Particle", CSnow::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Firework_Particle", CFirework::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Vortex_Particle", CVortexParticle::Create(m_pGraphicDev)), E_FAIL);

	/////////////////////////// 파티클 텍스쳐 
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Smoke_Texture", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Resource/Texture2D/Particle/smoke.png")), E_FAIL);

	Set_String(L"Buffer Loading..........");


	Set_String(L"AI Loading..........");
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"TSK_Move", CMoveLook::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"TSK_Rot", CRotToFace::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"TSK_Wait", CWait::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"TSK_RandomLook", CRandomLook::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"TSK_Jump", CJump::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"TSK_Attack", CAttack::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"TSK_Evasion", CEvasion::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"TSK_LeapJump", CLeapJump::Create(m_pGraphicDev)), E_FAIL);
	
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"DEC_RangeCheck", CRangeCheck::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Sequence", CSequence::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Selector", CSelector::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Root", CRoot::Create(m_pGraphicDev)), E_FAIL);

	Set_String(L"Room Loading..........");

	
	// ==임시 코드==
	const auto& uMapProto = Engine::CProtoMgr::GetInstance()->Get_ProtoMap();

	for (auto iter : uMapProto)
	{
		if (dynamic_cast<CTexture*>(iter.second))
			m_listTags.push_back(iter.first);
	}


	m_bFinish = true;
	
	Set_String(L"Loading Complete!!!!!!!!");

	return 0;
}

CLoading * CLoading::Create(LPDIRECT3DDEVICE9 pGraphicDev, LOADINGID eID)
{
	CLoading *	pInstance = new CLoading(pGraphicDev);

	if (FAILED(pInstance->Ready_Loading(eID)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CLoading::Free(void)
{
	WaitForSingleObject(m_hThread, INFINITE);
	CloseHandle(m_hThread);
	DeleteCriticalSection(&m_Crt);

	Safe_Release(m_pGraphicDev);
}
