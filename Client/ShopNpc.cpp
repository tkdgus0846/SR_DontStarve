#include "ShopNpc.h"
#include "Bullet.h"
#include "Export_Function.h"
#include "Player.h"
#include "SellItem.h"
CShopNpc::CShopNpc(LPDIRECT3DDEVICE9 pGraphicDev)
	: CMonster(pGraphicDev)
{
	Set_LayerID(LAYER_NPC);
	Set_ObjTag(L"ShopNpc");

	m_iHp = 1000;
}

CShopNpc::~CShopNpc()
{
}

HRESULT CShopNpc::Add_Component()
{
	CRcTex* RcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(RcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", RcTex });

	CTexture* Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"shopkeeperidle_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"shopkeeperidle_Texture", Texture });

	Ani = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(Ani, E_FAIL);

	Ani->BindAnimation(ANIM_IDLE, Texture, 0.1f);
	Ani->SelectState(ANIM_IDLE);
	m_uMapComponent[ID_ALL].insert({ L"Animation", Ani });

	Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"shopkeeperdamaged_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"shopkeeperdamaged_Texture", Texture });
	Ani->BindAnimation(ANIM_DAMAGED, Texture, 0.1f, FALSE);

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_ENEMY));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].emplace(L"BodyCollider", pCollider);
	pCollider->Set_BoundingBox({ 6.f, 6.f, 6.f });

	m_pTransform->Set_BillMode(true);

	return S_OK;
}

HRESULT CShopNpc::Ready_GameObject(void)
{
	m_pTransform->m_vScale = { 5.f, 5.f, 5.f };
	m_pTransform->Set_Pos(_vec3{ 30.f, 5.f, 30.f });
	m_pTransform->Set_MoveType(CTransform::LANDOBJECT);

	_vec3 Pos = m_pTransform->m_vInfo[INFO_POS];

	CSellItem* item1 = CSellItem::Create(m_pGraphicDev, Pos, SELL_WEAPON, 50, FLAMESHOT);
	Add_GameObject(item1);
	m_ItemList.push_back(item1);

	__super::Ready_GameObject();
	return S_OK;
}

_int CShopNpc::Update_GameObject(const _float & fTimeDelta)
{
	__super::Update_GameObject(fTimeDelta);

	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return OBJ_NOEVENT;
}

void CShopNpc::LateUpdate_GameObject(void)
{
	if (Ani->GetFinished())
	{
		Ani->AnimationClear();
		Ani->SelectState(ANIM_IDLE);
		m_redTexture = false;
	}

	__super::LateUpdate_GameObject();
}

void CShopNpc::Render_GameObject(void)
{
	__super::Render_GameObject();
}

void CShopNpc::Get_Damaged(_int Damage)
{
	__super::Get_Damaged(Damage);

	Ani->SelectState(ANIM_DAMAGED);
}

void CShopNpc::OnCollisionEnter(const Collision * collsion)
{

}

void CShopNpc::OnCollisionStay(const Collision * collision)
{
	if (dynamic_cast<CBullet*>(collision->OtherGameObject) &&
		collision->OtherCollider == collision->OtherGameObject->Get_Component(L"BodyCollider", ID_ALL) &&
		collision->MyCollider == Get_Component(L"BodyCollider", ID_ALL))
	{
		m_redTexture = true;
		m_fCurTime = Get_WorldTime();
		m_fPreTime = Get_WorldTime();
	}
}


CShopNpc * CShopNpc::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CShopNpc* pInstance = new CShopNpc(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}

	return pInstance;
}


void CShopNpc::Free(void)
{
	__super::Free();
}
