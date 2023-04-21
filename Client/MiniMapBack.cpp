#include "MiniMapBack.h"
#include "Export_Function.h"


CMiniMapBack::CMiniMapBack(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUI(pGraphicDev)
{
	Set_ObjTag(L"MiniMapBack");
}

CMiniMapBack::~CMiniMapBack()
{
}

HRESULT CMiniMapBack::Add_Component()
{
	for (size_t i = 0; i < m_arrMap.size(); i++)
	{
		m_pRcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
		NULL_CHECK_RETURN(m_pRcTex, E_FAIL);
		m_arrMap[i] = m_pRcTex;
	} 

	m_pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"MiniMapBack_Texture", this));
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"MiniMapBack_Texture", m_pTexture });

	return S_OK;
}

HRESULT CMiniMapBack::Ready_GameObject(void)
{
	m_vScale = { 24.f, 24.f , 0.f };
	__super::Ready_GameObject();

	return S_OK;
}

_int CMiniMapBack::Update_GameObject(const _float & fTimeDelta)
{
	Engine::Add_RenderGroup(RENDER_ALPHA_UI, this);

	__super::Update_GameObject(fTimeDelta);
	return 0;
}

void CMiniMapBack::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CMiniMapBack::Render_GameObject(void)
{

	__super::Render_GameObject();
}


CMiniMapBack * CMiniMapBack::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMiniMapBack* pInstance = new CMiniMapBack(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CMiniMapBack::Free(void)
{
	auto iter = m_arrMap.begin();
	for (; iter < m_arrMap.end(); iter++)
	{
		Safe_Release(*iter);
	}

	__super::Free();
}
