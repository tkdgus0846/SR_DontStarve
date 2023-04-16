#include "Guppi.h"

#include "Export_Function.h"

CGuppi::CGuppi(LPDIRECT3DDEVICE9 pGraphicDev)
	:CMonster(pGraphicDev)
{
	Set_ObjTag(L"Guppi");

}

CGuppi::~CGuppi()
{
}

HRESULT CGuppi::Ready_GameObject(const _vec3& vPos)
{
	m_fSpeed = 10.f;

	m_pTransform->m_vScale = { 1.f, 1.f, 1.f };
	m_pTransform->m_vInfo[INFO_POS] = vPos;
	m_pTransform->Set_MoveType(CTransform::AIRCRAFT);

	HRESULT result = __super::Ready_GameObject();

	return S_OK;
}

_int CGuppi::Update_GameObject(const _float & fTimeDelta)
{
	__super::Update_GameObject(fTimeDelta);

	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return S_OK;
}

void CGuppi::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CGuppi::Render_GameObject(void)
{
	__super::Render_GameObject();
}

HRESULT CGuppi::Add_Component()
{
	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_Guppi_Blue_Texture", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"Monster_Guppi_Blue_Texture", texture });

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
	pCollider->Set_BoundingBox({ 0.6f, 0.6f, 0.6f });

	pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Range", this, COL_DETECTION));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Range", pCollider });
	pCollider->Set_BoundingBox({ 50.f, 10.f, 50.f });

	pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"EvasBullet", this, COL_DETECTION));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"EvasBullet", pCollider });
	pCollider->Set_BoundingBox({ 2.5f, 2.5f, 2.5f });

	FAILED_CHECK_RETURN(Create_Root_AI(), E_FAIL);
	FAILED_CHECK_RETURN(Set_PatrolAndFollow_AI(), E_FAIL);
	FAILED_CHECK_RETURN(Init_AI_Behaviours(), E_FAIL);

	return S_OK;
}

CGuppi * CGuppi::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos)
{
	CGuppi* pInstance = new CGuppi(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(vPos)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CGameObject * CGuppi::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CGuppi* pInstance = new CGuppi(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(_vec3{})))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CGuppi::Free(void)
{
	__super::Free();
}
