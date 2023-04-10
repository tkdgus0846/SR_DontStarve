#include "Bub.h"

#include "Export_Function.h"

CBub::CBub(LPDIRECT3DDEVICE9 pGraphicDev)
	:CMonster(pGraphicDev)
{
}

CBub::~CBub()
{
}

HRESULT CBub::Ready_GameObject(void)
{
	m_fSpeed = 10.f;
	m_iAttack = 1;
	m_iHp = 5;

	m_pTransform->m_vScale = { 1.f, 1.f, 1.f };
	m_pTransform->m_vInfo[INFO_POS] = { 4.f, 0.8f, 15.f };
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

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", this, COL_ENEMY));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"BodyCollider", pCollider });
	pCollider->Set_BoundingBox({ 2.5f, 2.5f, 2.5f });

	//pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", this, COL_DETECTION));
	//NULL_CHECK_RETURN(pCollider, E_FAIL);
	//m_uMapComponent[ID_ALL].insert({ L"Range", pCollider });
	//pCollider->Set_BoundingBox({ 50.f, 10.f, 50.f });

	pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", this, COL_DETECTION));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Range", pCollider });
	pCollider->Set_BoundingBox({ 30.f, 10.f, 30.f });

	pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", this, COL_DETECTION));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"EvasBullet", pCollider });
	pCollider->Set_BoundingBox({ 2.5f, 2.5f, 2.5f });

	CRigidbody* pRigidBody = dynamic_cast<CRigidbody*>(Engine::Clone_Proto(L"RigidBody", this));
	NULL_CHECK_RETURN(pRigidBody, E_FAIL);
	m_uMapComponent[ID_UPDATE].insert({ L"RigidBody", pRigidBody });

	Set_PatrolAndFollow_AI();

	return S_OK;
}

CBub * CBub::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBub* pInstance = new CBub(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
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
