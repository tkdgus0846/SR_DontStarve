#include "WeaponType.h"
#include "Export_Function.h"


CWeaponType::CWeaponType(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUI(pGraphicDev)
{
}

CWeaponType::~CWeaponType()
{
}

HRESULT CWeaponType::Add_Component()
{
	m_pRcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(m_pRcTex, E_FAIL);

	CTexture* Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Weapon_bigshot_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_arrTexture[BIGSHOT] = Texture;

	Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Weapon_explosiveshot_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_arrTexture[EXPLOSIVESHOT] = Texture;	

	Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Weapon_flameshot_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_arrTexture[FLAMESHOT] = Texture;

	Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Weapon_rapidshot_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_arrTexture[RAPIDSHOT] = Texture;

	Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Weapon_spreadshot_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_arrTexture[SPREADSHOT] = Texture;

	Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Weapon_freezeshot_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_arrTexture[FREEZESHOT] = Texture;

	Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Weapon_lasershot_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_arrTexture[LASERSHOT] = Texture;

	return S_OK;
}

HRESULT CWeaponType::Ready_GameObject(void)
{
	__super::Ready_GameObject();

	return S_OK;
}

_int CWeaponType::Update_GameObject(const _float & fTimeDelta)
{
	__super::Update_GameObject(fTimeDelta);

	return 0;
}

void CWeaponType::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CWeaponType::Render_GameObject(void)
{
	WEAPONTYPE type = FREEZESHOT;
	Set_ViewMatrix_UI();
	dynamic_cast<CTexture*>(m_arrTexture[type])->Render_Texture();
	m_pRcTex->Render_Component();
}

void CWeaponType::Set_ViewMatrix_UI()
{
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);

	_matrix matTrans;
	D3DXMatrixScaling(&matView, 25.f, 25.f, 0.f);
	D3DXMatrixTranslation(&matTrans, -341.f, -230.f, 0.f);
	D3DXMatrixMultiply(&matView, &matView, &matTrans);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
}

CWeaponType * CWeaponType::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CWeaponType* pInstance = new CWeaponType(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CWeaponType::Free(void)
{
	Safe_Release(m_pRcTex);
	for_each(m_arrTexture.begin(), m_arrTexture.end(), CDeleteObj());
	__super::Free();
}
