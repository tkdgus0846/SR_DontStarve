#include "Door.h"

#include "Export_Function.h"

CDoor::CDoor(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CDoor::~CDoor()
{
}

HRESULT CDoor::Ready_GameObject(void)
{
	HRESULT Result = __super::Ready_GameObject();

	return Result;
}

_int CDoor::Update_GameObject(const _float & fTimeDelta)
{
	__super::Update_GameObject(fTimeDelta);

	return 0;
}

void CDoor::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CDoor::Render_GameObject(void)
{
}

HRESULT CDoor::Add_Component()
{
	CRcTex* pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(pBufferCom, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"RcTex", pBufferCom });

	m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Dock_Texture", this));
	NULL_CHECK_RETURN(m_pTextureCom);
	m_uMapComponent[ID_RENDER].emplace(L"Dock_Texture", m_pTextureCom);
	
	return S_OK;
}

CDoor * CDoor::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CDoor* pInstance = new CDoor(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CDoor::Free(void)
{
	__super::Free();
}
