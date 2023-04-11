#include "stdafx.h"
#include "Floor.h"

#include "Export_Function.h"

CFloor::CFloor(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
	Set_LayerID(LAYER_ENVIRONMENT);
	Set_ObjTag(L"Floor");
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
	__super::Render_GameObject();
}

HRESULT CFloor::Add_Component(void)
{
	CComponent* pComp;
	pComp = dynamic_cast<CFloorTex*>(Engine::Clone_Proto(L"FloorTex",this));
	NULL_CHECK_RETURN(pComp, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"FloorTex", pComp });

	pComp = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Floor_Level1_Texture",this));
	NULL_CHECK_RETURN(pComp, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"Floor_Level1_Texture", pComp });

	pComp = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Collider", this, COL_ENVIRONMENT));
	NULL_CHECK_RETURN(pComp, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Collider", pComp });


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