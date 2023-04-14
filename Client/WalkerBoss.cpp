#include "WalkerBoss.h"

#include "Export_Function.h"

CWalkerBoss::CWalkerBoss(LPDIRECT3DDEVICE9 pGraphicDev)
	:CMonster(pGraphicDev)
{
}

CWalkerBoss::~CWalkerBoss()
{
}

HRESULT CWalkerBoss::Ready_GameObject(const _vec3 & vPos)
{
	m_fSpeed = 10.f;
	m_iAttack = 1;
	m_iHp = 5;

	m_pTransform->m_vScale = { 3.f, 3.f, 3.f };
	m_pTransform->m_vInfo[INFO_POS] = vPos;
	m_pTransform->Set_MoveType(CTransform::LANDOBJECT);

	HRESULT result = __super::Ready_GameObject();

	return result;
}

_int CWalkerBoss::Update_GameObject(const _float & fTimeDelta)
{
	__super::Update_GameObject(fTimeDelta);
	if (GetDead()) return OBJ_DEAD;

	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return 0;
}

void CWalkerBoss::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CWalkerBoss::Render_GameObject(void)
{
	__super::Render_GameObject();
}

HRESULT CWalkerBoss::Add_Component()
{
	CTexture* pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_WalkerBoss_Walk_Texture", this));
	NULL_CHECK_RETURN(pTexture, E_FAIL);
	m_uMapComponent[ID_STATIC].emplace(L"Monster_WalkerBoss_Walk_Texture", pTexture);
	
	CAnimation* pAnimation = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(pAnimation, E_FAIL);
	m_uMapComponent[ID_ALL].emplace(L"Animation", pAnimation);

	pAnimation->BindAnimation(ANIM_WALK, pTexture, 0.3f);
	pAnimation->SelectState(ANIM_WALK);

	pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_WalkerBoss_Idle_Texture", this));
	NULL_CHECK_RETURN(pTexture, E_FAIL);
	m_uMapComponent[ID_STATIC].emplace(L"Monster_WalkerBoss_Idle_Texture", pTexture);
	pAnimation->BindAnimation(ANIM_IDLE, pTexture, 0.3f);

	CRcTex* pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(pBufferCom, E_FAIL);
	m_uMapComponent[ID_RENDER].emplace(L"RcTex", pBufferCom);

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_ENEMY));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].emplace(L"BodyCollider", pCollider);
	pCollider->Set_BoundingBox({ 6.f, 6.f, 6.f });

	pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Range", this, COL_DETECTION));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].emplace(L"Range", pCollider);
	pCollider->Set_BoundingBox({ 70.f, 10.f, 70.f });

	pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"EvasBullet", this, COL_DETECTION));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].emplace(L"EvasBullet", pCollider);
	pCollider->Set_BoundingBox({ 15.f, 6.f, 15.f });

	FAILED_CHECK_RETURN(Create_Root_AI(), E_FAIL);
	FAILED_CHECK_RETURN(Set_Boss2_AI(), E_FAIL);
	FAILED_CHECK_RETURN(Init_AI_Behaviours(), E_FAIL);

	return S_OK;
}

CWalkerBoss * CWalkerBoss::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3 & vPos)
{
	CWalkerBoss* pInstance = new CWalkerBoss(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(vPos)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CWalkerBoss::Free(void)
{
	__super::Free();
}
