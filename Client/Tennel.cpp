#include "Tennel.h"

#include "Export_Function.h"

CTennel::CTennel(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CTennel::~CTennel()
{
}

HRESULT CTennel::Ready_GameObject(void)
{
	HRESULT Result = __super::Ready_GameObject();

	m_pTransform->m_vScale = { 5.f, 5.f, 5.f };

	return Result;
}

_int CTennel::Update_GameObject(const _float & fTimeDelta)
{
	__super::Update_GameObject(fTimeDelta);

	__super::Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return 0;
}

void CTennel::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CTennel::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());

	__super::Render_GameObject();
}

HRESULT CTennel::Add_Component()
{
	CCubeTex* pBufferCom = dynamic_cast<CCubeTex*>(Engine::Clone_Proto(L"CubeTex", this));
	NULL_CHECK_RETURN(pBufferCom, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"CubeTex", pBufferCom });

	m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Level1_Tennel_Texture", this));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"Level1_Tennel_Texture", m_pTextureCom });

	m_pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", this));
	NULL_CHECK_RETURN(m_pCollider, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"Collider", m_pCollider });

	return S_OK;
}

void CTennel::Set_Position(_int iFrontorBack)
{
	if (0 == iFrontorBack)	// front ÀÎ °æ¿ì
	{
		//m_pCollider->Set_BoundingBox({ 5.f, 5.f, 1.f }, )
	}
	else
	{

	}
}

CTennel * CTennel::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTennel* pInstance = new CTennel(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CTennel::Free(void)
{
	__super::Free();
}
