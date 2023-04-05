#include "NormalWeapon.h"
#include "Export_Function.h"

CNormalWeapon::CNormalWeapon(LPDIRECT3DDEVICE9 pGraphicDev) :
	CWeapon(pGraphicDev)
{
}

CNormalWeapon::~CNormalWeapon()
{
}

void CNormalWeapon::Shot()
{
	if (CanShot())
	{
		/*CNormalBullet* bullet = CBulletMgr::GetInstance()->Pop<CNormalBullet>(L"NormalBullet", m_pGraphicDev, bulletPosition, vDir, false);
		Add_GameObject(LAYER_BULLET, L"Bullet", bullet);
		m_bShooted = true;*/
	}
}

_int CNormalWeapon::Update_GameObject(const _float& fTimeDelta)
{
	return __super::Update_GameObject(fTimeDelta);
}

HRESULT CNormalWeapon::Add_Component()
{

	/*CRcTex* rcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(rcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", rcTex });*/
	return S_OK;
}

HRESULT CNormalWeapon::Ready_GameObject(void)
{
	return __super::Ready_GameObject();
}

void CNormalWeapon::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CNormalWeapon::Render_GameObject(void)
{
	
	__super::Render_GameObject();
}

CNormalWeapon* CNormalWeapon::Create(LPDIRECT3DDEVICE9 pGraphicDev, CTransform* pOnwerTransform)
{
	CNormalWeapon*		pInstance = new CNormalWeapon(pGraphicDev);
	pInstance->m_pOwnerTransform = pOnwerTransform;

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CNormalWeapon::Free(void)
{
	__super::Free();
}