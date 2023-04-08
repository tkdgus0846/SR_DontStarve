#include "BulletGauge.h"
#include "Export_Function.h"



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


	m_pBufferCom->Edit_VB(m_VBGuage);
	m_VBGuage -= 0.001f;


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
	Set_VeiwMatrix_UI();

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

void CBulletGauge::Set_VeiwMatrix_UI()
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






