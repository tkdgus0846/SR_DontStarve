#include "Pyramid.h"
#include "Export_Function.h"
#include "Bullet.h"

CPyramid::CPyramid(LPDIRECT3DDEVICE9 pGraphicDev) :
	CMapObj(pGraphicDev)
{
	
}

CPyramid::~CPyramid()
{
}

HRESULT CPyramid::Ready_GameObject(void)
{
	HRESULT result = __super::Ready_GameObject();

	// 임시 코드
	m_pTransform->Set_Pos({ 25.f, 0.f, 25.f });
	
	m_pTransform->Set_Scale({ 2.5f, 3.f, 2.5f });
	return result;
}

_int CPyramid::Update_GameObject(const _float & fTimeDelta)
{
	if (GetDead())
		return OBJ_DEAD;

	__super::Update_GameObject(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_NONALPHA, this);

	return OBJ_NOEVENT;
}

void CPyramid::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CPyramid::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());

	__super::Render_GameObject();
}

HRESULT CPyramid::Add_Component()
{
	CComponent *pComponent;

	pComponent = dynamic_cast<CFrustrumNormalTex*>(Engine::Clone_Proto(L"FrustrumNormalTex", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"FrustrumNormalTex", pComponent });

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_TRIGGER));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"BodyCollider", pCollider });
	pCollider->Set_BoundingBox(m_pTransform->Get_Scale() * 4.f);
	return S_OK;
}

void CPyramid::Free(void)
{
	__super::Free();
}
