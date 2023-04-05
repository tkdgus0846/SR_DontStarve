#include "stdafx.h"
#include "NormalBullet.h"

#include "Export_Function.h"
#include "BulletMgr.h"

CNormalBullet::CNormalBullet(LPDIRECT3DDEVICE9 pGraphicDev) :
	CBullet(pGraphicDev)
{
	m_fSpeed = 30.f;
	m_fLifeSpan = 2.f;
	m_fAge = 0.f;
}

CNormalBullet::~CNormalBullet()
{
}

void CNormalBullet::SetDead()
{
	CBulletMgr::GetInstance()->Push(L"NormalBullet", this);
}

HRESULT CNormalBullet::Ready_GameObject(void)
{
	HRESULT result = __super::Ready_GameObject();


	return result;
}

_int CNormalBullet::Update_GameObject(const _float& fTimeDelta)
{
	if (Aging(fTimeDelta) == OBJ_RETPOOL) return OBJ_RETPOOL;

	/*m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());*/

	

	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);
	
	_matrix view;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &view);
	//m_pTransform->Set_Billboard(&view);

	__super::Update_GameObject(fTimeDelta);
	
	m_pTransform->Move_Walk(m_fSpeed*2.f, fTimeDelta);

	Add_RenderGroup(RENDER_ALPHA, this);

	return OBJ_NOEVENT;
}

void CNormalBullet::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CNormalBullet::Render_GameObject(void)
{
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	__super::Render_GameObject();

	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

void CNormalBullet::OnCollisionEnter(const Collision* collsion)
{
	
}

void CNormalBullet::OnCollisionStay(const Collision* collision)
{
	
}

void CNormalBullet::OnCollisionExit(const Collision* collision)
{
	
}

HRESULT CNormalBullet::Add_Component()
{
	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"NormalBullet_Texture", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"NormalBullet_Texture", texture });

	CAnimation* animation = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(animation, E_FAIL);

	animation->BindAnimation(ANIM_SHOT, texture, 0.1f);
	animation->SelectState(ANIM_SHOT);
	m_uMapComponent[ID_ALL].insert({ L"Animation", animation });

	CRcTex* rcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(rcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", rcTex });

	return S_OK;
}

void CNormalBullet::Free(void)
{
	__super::Free();
}

CNormalBullet* CNormalBullet::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CNormalBullet*		pInstance = new CNormalBullet(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}
