#include "TreeBoss.h"

#include "Export_Function.h"

CTreeBoss::CTreeBoss(LPDIRECT3DDEVICE9 pGraphicDev)
	:CMonster(pGraphicDev)
{
	Set_LayerID(LAYER_MONSTER);
}

CTreeBoss::~CTreeBoss()
{
}

HRESULT CTreeBoss::Ready_GameObject(const _vec3 & vPos)
{
	m_fSpeed = 10.f;
	m_iAttack = 1;
	m_iHp = 100;
	m_iMaxHp = 100;

	m_pTransform->m_vScale = { 4.f, 4.f, 4.f };
	m_pTransform->m_vInfo[INFO_POS] = vPos;
	m_pTransform->Set_MoveType(CTransform::LANDOBJECT);

	HRESULT result = __super::Ready_GameObject();

	return result;
}

_int CTreeBoss::Update_GameObject(const _float & fTimeDelta)
{
	__super::Update_GameObject(fTimeDelta);

	if (GetDead()) 
		return OBJ_DEAD;

	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return OBJ_NOEVENT;
}

void CTreeBoss::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CTreeBoss::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	__super::Render_GameObject();
}

HRESULT CTreeBoss::Add_Component()
{
	CAnimation* animation = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(animation, E_FAIL);
	m_uMapComponent[ID_ALL].emplace(L"Animation", animation);
	animation->SelectState(ANIM_IDLE);

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_TreeBoss_Summon_Texture", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].emplace(L"Monster_TreeBoss_Summon_Texture", texture);
	animation->BindAnimation(ANIM_ATTACK, texture, 0.25f);

	texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_TreeBoss_Idle_Texture", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].emplace(L"Monster_TreeBoss_Idle_Texture", texture);
	animation->BindAnimation(ANIM_IDLE, texture, 0.25f);

	CRcTex* rcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(rcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", rcTex });

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_ENEMY));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"BodyCollider", pCollider });
	pCollider->Set_BoundingBox({ 8.f, 8.f, 8.f });

	pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Range", this, COL_DETECTION));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Range", pCollider });
	pCollider->Set_BoundingBox({ 70.f, 10.f, 70.f });

	FAILED_CHECK_RETURN(Create_Root_AI(), E_FAIL);
	//FAILED_CHECK_RETURN(Set_Boss1_AI(), E_FAIL);
	FAILED_CHECK_RETURN(Init_AI_Behaviours(), E_FAIL);

	return S_OK;
}

CTreeBoss * CTreeBoss::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3 & vPos)
{
	CTreeBoss* pInstance = new CTreeBoss(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(vPos)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CTreeBoss::Free(void)
{
	__super::Free();
}
