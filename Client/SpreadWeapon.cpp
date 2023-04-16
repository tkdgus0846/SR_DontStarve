#include "SpreadWeapon.h"
#include "Export_Function.h"

#include "BulletMgr.h"
#include "NormalBullet.h"
#include "IceBullet.h"

CSpreadWeapon::CSpreadWeapon(LPDIRECT3DDEVICE9 pGraphicDev) :
	CWeapon(pGraphicDev)
{
	Set_ObjTag(L"SpreadWeapon");

	m_fCycle = 0.9f;
	m_MaxBulletNum = 30;
	m_CurBulletNum = 30;
}

CSpreadWeapon::~CSpreadWeapon()
{
}

CBullet* CSpreadWeapon::Shot_Setting()
{
	CCamera* playerCamera = dynamic_cast<CCamera*>(Get_Player()->Get_Component(L"Player_Camera", ID_UPDATE));

	if (playerCamera == nullptr) return nullptr;


	VIEWPARAMS* cameraViewparams = playerCamera->Get_Camera_ViewParams();
	_vec3 cameraAt = cameraViewparams->vAt;
	_vec3 cameraEye = cameraViewparams->vEye;

	_vec3 look = cameraAt - cameraEye;

	look = look*30.f;

	cameraAt = cameraEye + look;


	_vec3 bulletDir = cameraAt - m_pTransform->m_vInfo[INFO_POS];
	bulletDir.Normalize();

	CBullet* bullet = CBulletMgr::GetInstance()->Pop(L"NormalBullet", m_pGraphicDev, m_pTransform->m_vInfo[INFO_POS], bulletDir, {0.5f,0.5f,1.f}, false, 40.f);

	m_CurBulletNum++;

	return bullet;	
}

_int CSpreadWeapon::Update_GameObject(const _float& fTimeDelta)
{
	return __super::Update_GameObject(fTimeDelta);
}

HRESULT CSpreadWeapon::Add_Component()
{
	return S_OK;
}

HRESULT CSpreadWeapon::Ready_GameObject(void)
{
	return __super::Ready_GameObject();
}

void CSpreadWeapon::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CSpreadWeapon::Render_GameObject(void)
{
	
	__super::Render_GameObject();
}

CSpreadWeapon* CSpreadWeapon::Create(LPDIRECT3DDEVICE9 pGraphicDev, CTransform* pOnwerTransform)
{
	CSpreadWeapon*		pInstance = new CSpreadWeapon(pGraphicDev);
	pInstance->m_pOwnerTransform = pOnwerTransform;

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CSpreadWeapon::Free(void)
{
	__super::Free();
}
