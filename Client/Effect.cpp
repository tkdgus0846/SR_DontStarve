#include "Effect.h"
#include "Export_Function.h"

#include "EffectManager.h"

CEffect::CEffect(LPDIRECT3DDEVICE9 pGraphicDev) :
	CGameObject(pGraphicDev),
	m_fAge(0.f),
	m_pAnimation(nullptr)
{
	Set_LayerID(LAYER_EFFECT);
	Set_ObjTag(L"Effect");
}

CEffect::~CEffect()
{
}

HRESULT CEffect::Add_Component()
{
	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(m_TextureName, this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"EffectTexture", texture });

	m_pAnimation = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(m_pAnimation, E_FAIL);

	m_pAnimation->BindAnimation(ANIM_RUN, texture, m_fAnimationTime, (m_bEndByTime==FALSE) ? FALSE:TRUE );
	m_pAnimation->SelectState(ANIM_RUN);
	m_uMapComponent[ID_ALL].insert({ L"Animation", m_pAnimation });

	CRcTex* rcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(rcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", rcTex });

	m_pTransform->Set_BillMode(true);
}

_int CEffect::Update_GameObject(const _float& fTimeDelta)
{
	if (m_bEndByTime == TRUE)
	{
		Aging(fTimeDelta);
		if (GetDead())
			return OBJ_RETPOOL;
	}
	
	_matrix viewMat;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &viewMat);
	
	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	__super::Update_GameObject(fTimeDelta);

	if (m_bEndByTime == FALSE)
	{
		if (m_pAnimation->GetFinished())
		{
			SetDead();
			return OBJ_RETPOOL;
		}
	}
	
	Add_RenderGroup(RENDER_ALPHA, this);
	return OBJ_NOEVENT;
}

void CEffect::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	__super::Render_GameObject();
}

void CEffect::SetDead(_bool bDead)
{
	__super::SetDead(bDead);

	if (bDead)
	{
		if (m_bEndByTime == false)
		{
			m_pAnimation->AnimationClear();
		}
		CEffectManager::GetInstance()->Push(m_TextureName, this);
		// ����Ʈ Ǯ�� �ٽ� Ǫ�����ִ°� �־�ߵ�. m_TextureName ����.
	}
}

CEffect* CEffect::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar* name, _float fAnimationTime, _bool bEndByTime, _float fLifeSpan)
{
	CEffect* effect = new CEffect(pGraphicDev);
	NULL_CHECK_RETURN_MSG(effect, nullptr, L"����Ʈ ��������");

	effect->m_TextureName = name;
	effect->m_fLifeSpan = fLifeSpan;
	effect->m_bEndByTime = bEndByTime;
	effect->m_fAnimationTime = fAnimationTime;
	effect->Ready_GameObject();
	//NULL_CHECK_RETURN_MSG(, nullptr, L"����Ʈ ���� ����");
	return effect;
}

void CEffect::Free(void)
{
	__super::Free();
}
