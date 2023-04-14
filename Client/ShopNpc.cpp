#include "ShopNpc.h"

#include "Export_Function.h"
CShopNpc::CShopNpc(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
}

CShopNpc::~CShopNpc()
{
}

HRESULT CShopNpc::Add_Component()
{
	return S_OK;
}

HRESULT CShopNpc::Ready_GameObject(void)
{
	__super::Ready_GameObject();
	return S_OK;
}

_int CShopNpc::Update_GameObject(const _float & fTimeDelta)
{
	Engine::Add_RenderGroup(RENDER_ALPHA, this);
	__super::Update_GameObject(fTimeDelta);

	return 0;
}

void CShopNpc::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CShopNpc::Render_GameObject(void)
{
	__super::Render_GameObject();
}

CShopNpc * CShopNpc::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CShopNpc* pInstance = new CShopNpc(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}

	return pInstance;
}

void CShopNpc::Free(void)
{
}
