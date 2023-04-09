#include "BulletGauge.h"
#include "Export_Function.h"
#include "Player.h"
#include "Weapon.h"

CBulletGauge::CBulletGauge(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUI(pGraphicDev)
{
}

CBulletGauge::~CBulletGauge()
{

}

HRESULT CBulletGauge::Ready_GameObject(void)
{
	__super::Ready_GameObject();

	return S_OK;
}

_int CBulletGauge::Update_GameObject(const _float & fTimeDelta)
{

	CWeapon* pWeapon = dynamic_cast<CPlayer*>(Engine::Get_Player())->Get_CurWeapon();

	switch (dynamic_cast<CPlayer*>(Engine::Get_Player())->Get_CurWeaponType())
	{
	case BIGSHOT: 
	{
		m_pBufferCom->Edit_VB(m_NormalGuage);
		_float Max = pWeapon->Get_MaxBulletNum();
		_float Cur = pWeapon->Get_CurBulletNum();

		m_NormalGuage = Cur / Max;
	}
		break;
	case EXPLOSIVESHOT:
		break;
	case FLAMESHOT: 
	{
		m_pBufferCom->Edit_VB(m_FlameGuage);
		_float Max = pWeapon->Get_MaxBulletNum();
		_float Cur = pWeapon->Get_CurBulletNum();
		m_FlameGuage = Cur / Max;
	}
		break;
	case RAPIDSHOT:
		break;
	case SPREADSHOT:
		break;
	case FREEZESHOT: 
	{
		m_pBufferCom->Edit_VB(m_IceGuage);
		_float Max = pWeapon->Get_MaxBulletNum();
		_float Cur = pWeapon->Get_CurBulletNum();
		m_IceGuage = Cur / Max; 
	}
		break;
	case LASERSHOT:
		break;
	}


	Engine::Add_RenderGroup(RENDER_UI, this);

	__super::Update_GameObject(fTimeDelta);

	return 0;
}


void CBulletGauge::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CBulletGauge::Render_GameObject(void)
{
	Set_ViewMatrix_UI();

	__super::Render_GameObject();
}

HRESULT CBulletGauge::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex_Dynamic", this));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex_Dynamic", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"BulletGauge_Texture", this));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"BulletGauge_Texture", pComponent });

	return S_OK;
}

void CBulletGauge::Set_ViewMatrix_UI()
{
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);

	D3DXMatrixScaling(&matView, m_GaugeScale, 12.f, 0.f);

	D3DXMATRIX translationMat;
	D3DXMatrixTranslation(&translationMat, m_GaugePos, -230.f, 0.f);
	D3DXMatrixMultiply(&matView, &matView, &translationMat);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
}

CBulletGauge * CBulletGauge::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBulletGauge* pInstance = new CBulletGauge(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CBulletGauge::Free(void)
{
	__super::Free();
}






