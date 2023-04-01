#include "stdafx.h"
#include "Room.h"
#include "GameObject.h"

#include "Export_Function.h"

CRoom::CRoom(LPDIRECT3DDEVICE9 pGraphicDev) :
	CGameObject(pGraphicDev)
{
}

CRoom::~CRoom()
{
}

HRESULT CRoom::Ready_GameObject(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransform->m_vScale = { 1.f, 1.f, 1.f };
	m_pTransform->m_vInfo[INFO_POS] = { 10.f, -4.f, 10.f };
	
	return S_OK;
}

_int CRoom::Update_GameObject(const _float & fTimeDelta)
{
	__super::Update_GameObject(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_NONALPHA, this);

	
	return 0;
}

void CRoom::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CRoom::Render_GameObject(void)
{

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, TRUE);


	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	//m_pTextureCom->Set_Texture(0);
	__super::Render_GameObject();
	

	

	
	//m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

HRESULT CRoom::Add_Component(void)
{
	CComponent*		pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRoomTex*>(Engine::Clone_Proto(L"RoomTex", this));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"RoomTex", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Room_Texture", this));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"Room_Texture", pComponent });

	pComponent  = dynamic_cast<CMesh*>(Engine::Clone_Proto(L"AirplaneMesh", this));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_uMapComponent[ID_DYNAMIC].insert({ L"AirplaneMesh", pComponent });

	return S_OK;
}

CRoom * CRoom::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRoom*		pInstance = new CRoom(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CRoom::Free(void)
{
	__super::Free();
}
