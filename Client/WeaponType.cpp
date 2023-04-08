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
	CRcTex* RcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(RcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", RcTex });

	//CTexture* Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"CrossHair_Texture", this));
	//NULL_CHECK_RETURN(Texture, E_FAIL);
	//m_uMapComponent[ID_STATIC].insert({ L"CrossHair_Texture", Texture });

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
	Set_VeiwMatrix_UI();

	__super::Render_GameObject();
}

void CWeaponType::Set_VeiwMatrix_UI()
{
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);

	D3DXMatrixScaling(&matView, 25.f, 25.f, 0.f);

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
	__super::Free();
}
