#include "stdafx.h"
#include "FloorTile.h"

#include "Export_Function.h"

CFloorTile::CFloorTile(LPDIRECT3DDEVICE9 pGraphicDev)
	: CTile(pGraphicDev)
	, m_pBufferCom(nullptr)
	, m_pTextureCom(nullptr)
{
}

CFloorTile::~CFloorTile()
{
}

HRESULT CFloorTile::Ready_GameObject(void)
{
	HRESULT result = CTile::Ready_GameObject();
	m_pTransform->m_vScale *= VTXITV * 0.5f;
	m_pTransform->Rot_Pitch(90.f, 1);
	return result;
}

_int CFloorTile::Update_GameObject(const _float & fTimeDelta)
{
	CTile::Update_GameObject(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_NONALPHA, this);

	return 0;
}

void CFloorTile::LateUpdate_GameObject(void)
{
	CTile::LateUpdate_GameObject();
}

void CFloorTile::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());

	m_pTextureCom->Set_Texture_Num(0);

	CTile::Render_GameObject();
}

CFloorTile * CFloorTile::Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 vPos)
{
	CFloorTile*		pInstance = new CFloorTile(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	pInstance->m_pTransform->m_vInfo[INFO_POS] = vPos;

	return pInstance;
}

void CFloorTile::Free(void)
{
	CTile::Free();
}

HRESULT CFloorTile::Add_Component()
{
	m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"RcTex", m_pBufferCom });

	m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"NormalBullet_Texture", this));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"NormalBullet_Texture", m_pTextureCom });

	return S_OK;
}