#include "VortexBullet.h"
#include "BulletMgr.h"
#include "Monster.h"
#include "Effect.h"
#include "EffectManager.h"

#include "Export_Function.h"

CVortexBullet::CVortexBullet(LPDIRECT3DDEVICE9 pGraphicDev) :
	CBullet(pGraphicDev)
{
	Set_ObjTag(L"VortexBullet");
	m_fSpeed = 20.f;
	m_fLifeSpan = 4.f;
	m_fAge = 0.f;
	m_Damage = 0;
}

CVortexBullet::~CVortexBullet()
{

}

void CVortexBullet::SetDead(_bool bDead)
{
	__super::SetDead(bDead);
	if (bDead == true)
		CBulletMgr::GetInstance()->Push(L"VortexBullet", this);
}

HRESULT CVortexBullet::Ready_GameObject(void)
{
	HRESULT result = __super::Ready_GameObject();

	return result;
}

_int CVortexBullet::Update_GameObject(const _float & fTimeDelta)
{
	Aging(fTimeDelta);
	if (GetDead()) return OBJ_RETPOOL;

	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	_matrix viewMat;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &viewMat);
	//m_pTransform->Set_Billboard(&viewMat);

	__super::Update_GameObject(fTimeDelta);

	if (m_bHit == false)
	{
		m_Animation->Update_Component(fTimeDelta);
		m_pTransform->Move_Walk(m_fSpeed*2.f, fTimeDelta);
	}
	else
	{
		if (m_pTransform->m_vInfo[INFO_POS].y > 4.f)
		{
			m_pTransform->m_vInfo[INFO_POS].y -= 1.f*fTimeDelta;
		}

		if (m_pTransform->m_vScale.x < 2.f)
		{
			m_pTransform->m_vScale.x += 1.f*fTimeDelta;
			m_pTransform->m_vScale.y += 1.f*fTimeDelta;
		}

		// y 축으로 뺑뺑도는코드 넣어야됨.
		
	}
		
	Add_RenderGroup(RENDER_ALPHA, this);

	return OBJ_NOEVENT;
}

void CVortexBullet::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();

	if (m_bHit == false)
		m_Animation->LateUpdate_Component();
}

void CVortexBullet::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	
	__super::Render_GameObject();

	if (m_bHit == false)
		m_Animation->Render_Component();
	else
		m_AfterTexture->Render_Component();

	m_RcTex->Render_Component();
}

void CVortexBullet::OnCollisionEnter(const Collision * collsion)
{
	if (m_bHit == true) return;

	if (dynamic_cast<CMonster*>(collsion->OtherGameObject) != nullptr && collsion->MyCollider == Get_Component(L"BodyCollider", ID_ALL) && 
		collsion->OtherCollider == collsion->OtherGameObject->Get_Component(L"BodyCollider", ID_ALL))
	{
		if (m_bHit == false)
		{
			m_bHit = true;
			m_pTransform->Set_Scale({ 0.5f,0.5f,1.f });
		}
	}
	
}

void CVortexBullet::OnCollisionStay(const Collision * collision)
{
	
	if (m_bHit == true)
	{
		if (collision->MyCollider == Get_Component(L"RangeCollider", ID_ALL) &&
			dynamic_cast<CMonster*>(collision->OtherGameObject) != nullptr &&
			collision->OtherGameObject->Get_Component(L"BodyCollider", ID_ALL) == collision->OtherCollider)
		{
			// 끌여 당겨주는 코드.
		}
	}
}

void CVortexBullet::OnCollisionExit(const Collision * collision)
{
}

HRESULT CVortexBullet::Add_Component()
{
	m_AfterTexture  =  dynamic_cast<CTexture*>(Engine::Clone_Proto(L"VortexBulletAfter_Texture", this));
	NULL_CHECK_RETURN(m_AfterTexture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"VortexBulletAfter_Texture", m_AfterTexture });

	m_BeforeTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"VortexBulletBefore_Texture", this));
	NULL_CHECK_RETURN(m_BeforeTexture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"VortexBulletBefore_Texture", m_BeforeTexture });

	m_Animation = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(m_Animation, E_FAIL);

	m_Animation->BindAnimation(ANIM_SHOT, m_BeforeTexture, 0.1f);
	m_Animation->SelectState(ANIM_SHOT);
	m_uMapComponent[ID_STATIC].insert({ L"Animation", m_Animation });

	m_RcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(m_RcTex, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"RcTex", m_RcTex });

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_PLAYERBULLET));
	pCollider->Set_BoundingBox({ 1.5f, 1.5f, 1.5f });
	m_uMapComponent[ID_ALL].insert({ L"BodyCollider", pCollider });

	pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"RangeCollider", this, COL_PLAYERBULLET));
	pCollider->Set_BoundingBox({ 7.5f, 7.5f, 7.5f });
	m_uMapComponent[ID_ALL].insert({ L"RangeCollider", pCollider });

	return S_OK;
}

void CVortexBullet::Pop_Initialize()
{
	m_bHit = false;
}

void CVortexBullet::Free(void)
{
	__super::Free();
}

CVortexBullet * CVortexBullet::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CVortexBullet*		pInstance = new CVortexBullet(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}
