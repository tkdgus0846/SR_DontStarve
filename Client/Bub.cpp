#include "Bub.h"

#include "Export_Function.h"

CBub::CBub(LPDIRECT3DDEVICE9 pGraphicDev)
	:CMonster(pGraphicDev)
{
	Set_ObjTag(L"Bub");

}

CBub::~CBub()
{
}

HRESULT CBub::Ready_GameObject(const _vec3& vPos)
{
	m_fSpeed = 10.f;
	m_iAttack = 1;
	m_iHp = 1000;

	m_pTransform->m_vScale = { 2.4f, 2.4f, 2.4f };
	m_pTransform->m_vInfo[INFO_POS] = vPos;
	m_pTransform->Set_MoveType(CTransform::LANDOBJECT);

	HRESULT result = __super::Ready_GameObject();

	return S_OK;
}

_int CBub::Update_GameObject(const _float & fTimeDelta)
{
	__super::Update_GameObject(fTimeDelta);
	if (GetDead()) return OBJ_DEAD;

	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return OBJ_NOEVENT;
}

void CBub::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CBub::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());

	__super::Render_GameObject();
}

HRESULT CBub::Add_Component()
{
	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_Bub_Texture", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"Monster_Bub_Texture", texture });

	CAnimation* animation = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(animation, E_FAIL);

	animation->BindAnimation(ANIM_WALK, texture, 0.3f);
	animation->SelectState(ANIM_WALK);
	m_uMapComponent[ID_ALL].insert({ L"Animation", animation });

	CRcTex* rcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(rcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", rcTex });

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_ENEMY));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"BodyCollider", pCollider });
	pCollider->Set_BoundingBox({ 4.8f, 4.8f, 4.8f });

	pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Range", this, COL_DETECTION));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Range", pCollider });
	pCollider->Set_BoundingBox({ 70.f, 10.f, 70.f });

	pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"EvasBullet", this, COL_DETECTION));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"EvasBullet", pCollider });
	pCollider->Set_BoundingBox({ 15.f, 6.f, 15.f });

	Create_Root_AI();
	//Set_PatrolAndFollow_AI();
	//Set_PAF_JumpAI();
	//Set_PAF_LeapJumpAI();
	Set_Boss1_AI();
	Init_AI_Behaviours();

	return S_OK;
}

CBub * CBub::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos)
{
	CBub* pInstance = new CBub(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(vPos)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CBub::Free(void)
{
	__super::Free();
}
