#include "ShopNpc.h"
#include "Bullet.h"
#include "Export_Function.h"
#include "Player.h"
CShopNpc::CShopNpc(LPDIRECT3DDEVICE9 pGraphicDev)
	: CMonster(pGraphicDev)
{
	Set_ObjTag(L"ShopNpc");
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

	return S_OK;
}

HRESULT CShopNpc::Ready_GameObject(void)
{
	m_pTransform->m_vScale = { 5.f, 5.f, 5.f };
	m_pTransform->Set_Pos(_vec3{ 30.f, 5.f, 30.f });
	m_pTransform->Set_MoveType(CTransform::LANDOBJECT);

	__super::Ready_GameObject();
	return S_OK;
}

_int CShopNpc::Update_GameObject(const _float & fTimeDelta)
{
	if (CPlayer* pPlayer = dynamic_cast<CPlayer*>(Get_Player()))
	{
		m_pTransform->Set_Target(pPlayer->m_pTransform->m_vInfo[INFO_POS]);
		cout << pPlayer->m_pTransform->m_vInfo[INFO_POS].x << endl;
	}

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

void CShopNpc::OnCollisionEnter(const Collision * collsion)
{
	__super::OnCollisionEnter(collsion);

	if (true)
	{
		int a = 0;
	}
}

void CShopNpc::OnCollisionStay(const Collision * collision)
{
	__super::OnCollisionStay(collision);

	if (true)
	{
		int a = 0;
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
	Safe_Release(Ani);
	__super::Free();
}
