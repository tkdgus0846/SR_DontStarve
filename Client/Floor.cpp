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
	Key_Input(fTimeDelta);

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
	CComponent*		pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CFloorTex*>(Engine::Clone_Proto(L"FloorTex",this));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"FloorTex", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Floor_Texture",this));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"Floor_Texture", pComponent });

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

void CFloor::Key_Input(const _float & fTimeDelta)
{
	//_vec3		vDir;
	//m_pTransform->Get_Info(INFO_UP, &vDir);

	/*if (GetAsyncKeyState(VK_UP))	m_pTransform->Rotation(ROT_Y, D3DXToRadian(180.f * fTimeDelta));
	if (GetAsyncKeyState(VK_DOWN))	m_pTransform->Rotation(ROT_Y, D3DXToRadian(-180.f * fTimeDelta));*/

}