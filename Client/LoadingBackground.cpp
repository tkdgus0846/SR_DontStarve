#include "LoadingBackground.h"

#include "Export_Function.h"


CLoadingBackground::CLoadingBackground(LPDIRECT3DDEVICE9 pGraphicDev):
	CGameObject(pGraphicDev)
{
	Set_LayerID(LAYER_BACKGROUND);
	Set_ObjTag(L"Background");
}


CLoadingBackground::~CLoadingBackground()
{
}

CLoadingBackground* CLoadingBackground::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLoadingBackground*		pInstance = new CLoadingBackground(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

HRESULT CLoadingBackground::Add_Component()
{
	CComponent* pComponent;
	pComponent = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"Background_RcTex", pComponent });
	//m_BackgroundBuffer->Set_RenderFlag();

	pComponent = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Background_Texture", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"Background_Texture", pComponent });

	m_pTransform->Set_Scale({ (_float)WINCX, (_float)WINCY, 0.f });
	m_IdentityMatrix.Identity();
}

void CLoadingBackground::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_IdentityMatrix);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_IdentityMatrix);

	__super::Render_GameObject();
}

_int CLoadingBackground::Update_GameObject(const _float& fTimeDelta)
{
	__super::Update_GameObject(fTimeDelta);

	Add_RenderGroup(RENDER_NONALPHA, this);
	return 0;
}
