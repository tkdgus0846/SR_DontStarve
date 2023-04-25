#include "NubBoss.h"

#include "EffectManager.h"
#include "ItemManager.h"
#include "Export_Function.h"
#include "..\Engine\SoundMgr.h"

CNubBoss::CNubBoss(LPDIRECT3DDEVICE9 pGraphicDev)
	:CMonster(pGraphicDev)
{
	Set_LayerID(LAYER_BOSS);
	Set_ObjTag(L"NubBoss");
}

CNubBoss::~CNubBoss()
{
}

HRESULT CNubBoss::Ready_GameObject(const _vec3 & vPos)
{
	m_fSpeed = 10.f;
	m_iAttack = 1;
	m_iHp = 100;
	m_iMaxHp = 100;

	m_fCurTime1 = Get_WorldTime();
	m_fPreTime1 = Get_WorldTime();

	m_pTransform->m_vScale = { 2.4f, 2.4f, 2.4f };
	m_pTransform->m_vInfo[INFO_POS] = vPos;
	m_pTransform->Set_MoveType(CTransform::LANDOBJECT);

	HRESULT result = __super::Ready_GameObject();

	return S_OK;
}

_int CNubBoss::Update_GameObject(const _float & fTimeDelta)
{
	__super::Update_GameObject(fTimeDelta);

	if (GetDead() && Dead_Production())
		return OBJ_DEAD;
	else if (!GetDead())
		m_fPreTime1 = Get_WorldTime();

	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return OBJ_NOEVENT;
}

void CNubBoss::LateUpdate_GameObject(void)
{
	if (GetDead())
		return;

	__super::LateUpdate_GameObject();
}

void CNubBoss::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	__super::Render_GameObject();
}

_bool CNubBoss::Dead_Production()
{
	static _float fDest = 0.2f;
	m_fCurTime1 = Get_WorldTime();
	if (m_fCurTime1 - m_fPreTime1 < 3.5f)
	{
		_vec3 vEPos{};
		GetRandomVector(&vEPos, &_vec3(-3.f, -3.f, -3.f), &_vec3(3.f, 3.f, 3.f));
		_vec3 vPos = m_pTransform->m_vInfo[INFO_POS] + vEPos;
		GetRandomVector(&vEPos, &_vec3(1.f, 1.f, 1.f), &_vec3(1.7f, 1.7f, 1.7f));

		CEffect* pEffect = CEffectManager::GetInstance()->Pop(m_pGraphicDev, L"Explosion_Texture", vPos, vEPos, 0.1f);
		Add_GameObject(pEffect);

		if (m_fCurTime1 - m_fPreTime1 > fDest)
		{
			STOP_PLAY_SOUND(L"sfxExplode.wav", SOUND_ENEMY, 1.f);
			_vec3 pSpawnPos = m_pTransform->m_vInfo[INFO_POS];
			pSpawnPos.y += 3.f;
			CItem* item = CItemManager::GetInstance()->Pop(m_pGraphicDev, L"BulletItem", pSpawnPos);
			Add_GameObject(item);
			item = CItemManager::GetInstance()->Pop(m_pGraphicDev, L"CoinItem", pSpawnPos);
			Add_GameObject(item);
			fDest += 0.2f;
		}
		return false;
	}
	__super::SetDead(true);
	return true;
}

void CNubBoss::Get_Damaged(_int Damage)
{
	__super::Get_Damaged(Damage);

	_vec3 pSpawnPos = m_pTransform->m_vInfo[INFO_POS];
	pSpawnPos.y += 3.f;
	CItem* item = CItemManager::GetInstance()->Pop(m_pGraphicDev, L"BulletItem", pSpawnPos);
	Add_GameObject(item);
	item = CItemManager::GetInstance()->Pop(m_pGraphicDev, L"CoinItem", pSpawnPos);
	Add_GameObject(item);

}

HRESULT CNubBoss::Add_Component()
{
	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_NubBoss_Texture", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"Monster_NubBoss_Texture", texture });

	CAnimation* animation = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(animation, E_FAIL);

	animation->BindAnimation(ANIM_WALK, texture, 0.25f);
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

	FAILED_CHECK_RETURN(Create_Root_AI(), E_FAIL);
	FAILED_CHECK_RETURN(Set_Boss1_AI(), E_FAIL);
	FAILED_CHECK_RETURN(Init_AI_Behaviours(), E_FAIL);

	return S_OK;
}

CNubBoss * CNubBoss::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3 & vPos)
{
	CNubBoss* pInstance = new CNubBoss(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(vPos)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CNubBoss::Free(void)
{
	__super::Free();
}
