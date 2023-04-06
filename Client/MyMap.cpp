#include "MyMap.h"

#include "Room.h"
#include "Export_Function.h"

CMyMap::CMyMap(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
	for (auto iter : m_arrRoom)
		iter = nullptr;
}

CMyMap::~CMyMap()
{
}

HRESULT CMyMap::Ready_GameObject(void)
{
	Create_Default_Room();

	return __super::Ready_GameObject();
}

_int CMyMap::Update_GameObject(const _float & fTimeDelta)
{
	/*for (auto Room : m_arrRoom)
		Room->Update_GameObject(fTimeDelta);*/
	m_arrRoom[0]->Update_GameObject(fTimeDelta);

	__super::Update_GameObject(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_NONALPHA, this);

	return 0;
}

void CMyMap::LateUpdate_GameObject(void)
{
	/*for (auto Room : m_arrRoom)
		Room->LateUpdate_GameObject();*/
	m_arrRoom[0]->LateUpdate_GameObject();

	__super::LateUpdate_GameObject();
}

void CMyMap::Render_GameObject(void)
{
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());

	m_pTextureCom->Set_Texture_Num();

	__super::Render_GameObject();

	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

HRESULT CMyMap::Add_Component()
{
	CComponent*		pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Floor_Texture", this));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"Map_Texture", pComponent });

	return S_OK;
}

void CMyMap::Create_Default_Room()
{
	//for (_uint i = 0; i < 5; ++i)
	//{
	//	for (_uint j = 0; j < 5; ++j)
	//	{
	//		_uint iIndex = i * 5 + j;

	//		CRoom* pRoom = CRoom::Create(m_pGraphicDev);

	//		pRoom->m_pTransform->m_vInfo[INFO_POS] = { j * 50.f, 0.f, i * 50.f };
	//		pRoom->Ready_GameObject();

	//		//Add_GameObject(LAYER_ENVIRONMENT, L"Room", pRoom);

	//		m_arrRoom[iIndex] = pRoom;
	//	}
	//}

	
	

	m_arrRoom[0] = CRoom::Create(m_pGraphicDev);

	//Add_GameObject(LAYER_ENVIRONMENT, L"Room", pRoom);
}

CMyMap * CMyMap::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMyMap*		pInstance = new CMyMap(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CMyMap::Free()
{
	Safe_Release(m_arrRoom[0]);

	__super::Free();
}