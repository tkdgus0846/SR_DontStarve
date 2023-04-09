#include "stdafx.h"
#include "Floor.h"

#include "Export_Function.h"

CFloor::CFloor(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
}

CFloor::~CFloor()
{
}

HRESULT CFloor::Ready_GameObject(void)
{
	HRESULT result = __super::Ready_GameObject();

	return result;
}

_int CFloor::Update_GameObject(const _float& fTimeDelta)
{
	__super::Update_GameObject(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_NONALPHA, this);

	return 0;
}

void CFloor::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CFloor::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());

	m_pTextureCom->Set_Texture_Num();

	__super::Render_GameObject();
}

HRESULT CFloor::Add_Component(void)
{
	CFloorTex* pBufferCom = dynamic_cast<CFloorTex*>(Engine::Clone_Proto(L"FloorTex",this));
	NULL_CHECK_RETURN(pBufferCom, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"FloorTex", pBufferCom });

	m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Floor_Level1_Texture",this));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"Floor_Level1_Texture", m_pTextureCom });

	return S_OK;
}

CFloor* CFloor::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CFloor*		pInstance = new CFloor(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CFloor::Free(void)
{
	__super::Free();
}