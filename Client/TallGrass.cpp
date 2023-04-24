#include "TallGrass.h"
#include "Export_Function.h"

CTallGrass::CTallGrass(LPDIRECT3DDEVICE9 pGraphicDev)
	: CMapObj(pGraphicDev)
{
	Set_ObjTag(Tag());
}

CTallGrass::~CTallGrass()
{
}

HRESULT CTallGrass::Ready_GameObject(void)
{
	HRESULT result = __super::Ready_GameObject();

	return S_OK;
}

_int CTallGrass::Update_GameObject(const _float & fTimeDelta)
{
	if (GetDead())
		return OBJ_DEAD;

	__super::Update_GameObject(fTimeDelta);
	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return OBJ_NOEVENT;
}

void CTallGrass::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CTallGrass::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());

	__super::Render_GameObject();
}

HRESULT CTallGrass::Add_Component()
{
	CComponent *pComponent;

	pComponent = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", pComponent });

	pComponent = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Tall_Grass_Texture", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"Tall_Grass_Texture", pComponent });

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_OBJ));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"BodyCollider", pCollider });
	pCollider->Set_BoundingBox(m_pTransform->Get_Scale() * 4.f);

	return S_OK;
}



CGameObject * CTallGrass::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTallGrass* pInstance = new CTallGrass(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CTallGrass::Free(void)
{
	__super::Free();
}
