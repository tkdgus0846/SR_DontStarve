#include "stdafx.h"
#include "Wall.h"

#include "Export_Function.h"
CWall::CWall(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
}

CWall::~CWall()
{
}

HRESULT CWall::Ready_GameObject(void)
{
	HRESULT result = __super::Ready_GameObject();

	return result;
}

_int CWall::Update_GameObject(const _float & fTimeDelta)
{
	__super::Update_GameObject(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_NONALPHA, this);

	return 0;
}

void CWall::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CWall::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());

	m_pTextureCom->Set_Texture_Num();

	__super::Render_GameObject();

	m_pGraphicDev->SetTexture(0, nullptr);
}

HRESULT CWall::Add_Component()
{
	CComponent*		pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CWallTex*>(Engine::Clone_Proto(L"WallTex", this));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"WallTex", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Wall_Level1_Texture", this));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"Wall_Level1_Texture", pComponent });

	return S_OK;
}

CWall * CWall::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CWall*		pInstance = new CWall(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CWall::Free(void)
{
	__super::Free();
}
