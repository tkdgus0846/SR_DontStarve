#include "DiscItem.h"
#include "Export_Function.h"

CDiscItem::CDiscItem(LPDIRECT3DDEVICE9 pGraphicDev)
	: CItem(pGraphicDev)
{
}

CDiscItem::~CDiscItem()
{
}

HRESULT CDiscItem::Add_Component()
{
	CRcTex* RcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(RcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", RcTex });

	CTexture* Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Disc_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"DiscItem_Texture", Texture });

	CAnimation* Ani = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(Ani, E_FAIL);

	Ani->BindAnimation(ANIM_IDLE, Texture, 0.2f);
	Ani->SelectState(ANIM_IDLE);
	m_uMapComponent[ID_ALL].insert({ L"Animation", Ani });

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", this, COL_ITEM));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"BodyCollider", pCollider });
	pCollider->Set_BoundingBox({ 1.0f, 1.0f, 1.0f });


	return S_OK;
}

HRESULT CDiscItem::Ready_GameObject(void)
{
	_vec3 vScale = { 1.f, 1.f, 0.f };
	m_pTransform->Set_Pos(25.f, 1.f, 25.f);
	m_pTransform->Set_Scale(vScale);
	__super::Ready_GameObject();
	return S_OK;
}

_int CDiscItem::Update_GameObject(const _float & fTimeDelta)
{
	__super::Update_GameObject(fTimeDelta);

	if (GetDead()) return OBJ_DEAD;

	return OBJ_NOEVENT;
}

void CDiscItem::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CDiscItem::Render_GameObject(void)
{
	__super::Render_GameObject();
}

CDiscItem * CDiscItem::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CDiscItem* pInstance = new CDiscItem(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}

	return pInstance;
}

void CDiscItem::Free(void)
{
	__super::Free();
}
