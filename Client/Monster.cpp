#include "stdafx.h"
#include "Monster.h"

#include "Export_Function.h"
#include "MonoBehaviors.h"
#include "Player.h"
#include "Bullet.h"

CMonster::CMonster(LPDIRECT3DDEVICE9 pGraphicDev) : 
	CCreature(pGraphicDev),
	m_pRoot(nullptr), 
	m_redTexture(false)
{
	Set_LayerID(LAYER_MONSTER);
}

CMonster::~CMonster()
{
}

HRESULT CMonster::Ready_GameObject(void)
{
	HRESULT result = __super::Ready_GameObject();

	return result;
}

_int CMonster::Update_GameObject(const _float& fTimeDelta)
{
	if (GetDead()) return OBJ_DEAD;

	_matrix view;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &view);

	/*if (m_pTransform->m_vInfo[INFO_POS].y < 0.6f)
	{
		m_pTransform->m_vInfo[INFO_POS].y = 0.6f;
	}*/

	//m_pTransform->Set_Billboard(&view);
	__super::Update_GameObject(fTimeDelta);
	return 0;
}

void CMonster::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CMonster::Render_GameObject(void)
{
	if (m_redTexture)
	{
		m_fCurTime = Get_WorldTime();
		m_pGraphicDev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		m_pGraphicDev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		m_pGraphicDev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		m_pGraphicDev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

		m_pGraphicDev->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE2X);
		m_pGraphicDev->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
		m_pGraphicDev->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_TEXTURE);
		m_pGraphicDev->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		m_pGraphicDev->SetTextureStageState(1, D3DTSS_ALPHAARG1, D3DTA_CURRENT);
		m_pGraphicDev->SetTextureStageState(1, D3DTSS_ALPHAARG2, D3DTA_TFACTOR);
		float sparkleIntensity = 1.0f; // 0.0 (약함) ~ 1.0 (강함)
		m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_RGBA(static_cast<int>(255 * sparkleIntensity), 255, 255, 255));
	}

	__super::Render_GameObject();

	if (m_redTexture)
	{
		m_pGraphicDev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		m_pGraphicDev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		m_pGraphicDev->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

		m_pGraphicDev->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);

		if (m_fCurTime - m_fPreTime > m_fDuration)
			m_redTexture = false;
	}
}

void CMonster::OnCollisionEnter(const Collision * collsion)
{
	__super::OnCollisionEnter(collsion);

	CPlayer* player = dynamic_cast<CPlayer*>(collsion->OtherGameObject);

	if (player && collsion->MyCollider == Get_Component(L"BodyCollider", ID_ALL))
		player->Get_Damaged(Get_Attack());
}

void CMonster::OnCollisionStay(const Collision * collision)
{
	__super::OnCollisionStay(collision);

	if (dynamic_cast<CBullet*>(collision->OtherGameObject) &&
		collision->OtherCollider == collision->OtherGameObject->Get_Component(L"BodyCollider", ID_ALL) &&
		collision->MyCollider == Get_Component(L"BodyCollider", ID_ALL))
	{
		m_redTexture = true;
		m_fCurTime = Get_WorldTime();
		m_fPreTime = Get_WorldTime();
	}
}

void CMonster::OnCollisionExit(const Collision * collision)
{
	__super::OnCollisionExit(collision);
}

HRESULT CMonster::Add_Component(void)
{
	return S_OK;
}

CMonster* CMonster::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMonster*		pInstance = new CMonster(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CMonster::Free(void)
{
	__super::Free();
}

HRESULT CMonster::Create_Root_AI()
{
	m_pRoot = dynamic_cast<CRoot*>(Engine::Clone_Proto(L"Root", this));
	NULL_CHECK_RETURN(m_pRoot, E_FAIL);
	m_uMapComponent[ID_UPDATE].emplace(L"Root", m_pRoot);

	return S_OK;
}

// AI	구현부
CSequence* CMonster::Make_Patrol_AI(const _float& fWaitTime, const _float& fMoveTime)
{
	// 부품 생성
	CSequence* pSQPatrol = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQPatrol, nullptr);
	
	CMoveLook* pTaskMovePatrol = dynamic_cast<CMoveLook*>(Engine::Clone_Proto(L"TSK_Move", this));
	NULL_CHECK_RETURN(pTaskMovePatrol, nullptr);
	CRandomLook* pTaskRandomLook = dynamic_cast<CRandomLook*>(Engine::Clone_Proto(L"TSK_RandomLook", this));
	NULL_CHECK_RETURN(pTaskRandomLook, nullptr);
	CWait* pTaskWait = dynamic_cast<CWait*>(Engine::Clone_Proto(L"TSK_Wait", this));
	NULL_CHECK_RETURN(pTaskWait, nullptr);

	CIsNotRangeInPlayer* pDecFunc = dynamic_cast<CIsNotRangeInPlayer*>(Engine::Clone_Proto(L"DEC_IsNotRangeInPlayer", this));
	NULL_CHECK_RETURN(pDecFunc, nullptr);

	// 부품 초기설정
	pTaskWait->Set_Timer(fWaitTime);
	pTaskMovePatrol->Set_Timer(fMoveTime);
	pTaskMovePatrol->Set_Magnifi();

	// 부품 조립
	FAILED_CHECK_RETURN(pSQPatrol->Add_Decorator(pDecFunc), nullptr);

	FAILED_CHECK_RETURN(pSQPatrol->Add_Component(ID_UPDATE, L"TSK_RandomLook", pTaskRandomLook), nullptr);
	FAILED_CHECK_RETURN(pSQPatrol->Add_Component(ID_UPDATE, L"TSK_MovePatrol", pTaskMovePatrol), nullptr);
	FAILED_CHECK_RETURN(pSQPatrol->Add_Component(ID_UPDATE, L"TSK_Wait", pTaskWait), nullptr);

	return pSQPatrol;
}

CSequence* CMonster::Make_Follow_AI(const _float& fTimer)
{
	// 부품 생성
	CSequence* pSQChase = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQChase, nullptr);

	CMoveLook* pTskMovePlayer = dynamic_cast<CMoveLook*>(Engine::Clone_Proto(L"TSK_Move", this));
	NULL_CHECK_RETURN(pTskMovePlayer, nullptr);
	CLookAtTarget* pTskLookAtTarget = dynamic_cast<CLookAtTarget*>(Engine::Clone_Proto(L"TSK_LookAtTarget", this));
	NULL_CHECK_RETURN(pTskLookAtTarget, nullptr);

	CIsRangeInPlayer* pDecIsRangeInPlayer = dynamic_cast<CIsRangeInPlayer*>(Engine::Clone_Proto(L"DEC_IsRangeInPlayer", this));
	NULL_CHECK_RETURN(pDecIsRangeInPlayer, nullptr);
	CTimeInLimit* pDecTimeInLimit = dynamic_cast<CTimeInLimit*>(Engine::Clone_Proto(L"DEC_TimeInLimit", this));
	NULL_CHECK_RETURN(pDecTimeInLimit, nullptr);

	// 부품 초기설정
	pDecTimeInLimit->Set_Timer(fTimer);
	pTskMovePlayer->Set_Magnifi();

	// 부품 조립
	FAILED_CHECK_RETURN(pSQChase->Add_Decorator(pDecIsRangeInPlayer), nullptr);
	FAILED_CHECK_RETURN(pSQChase->Add_Decorator(pDecTimeInLimit), nullptr);

	FAILED_CHECK_RETURN(pSQChase->Add_Component(ID_UPDATE, L"TSK_LookAtTarget", pTskLookAtTarget), nullptr);
	FAILED_CHECK_RETURN(pSQChase->Add_Component(ID_UPDATE, L"TSK_MovePlayer", pTskMovePlayer), nullptr);

	return pSQChase;
}

CSequence* CMonster::Make_JumpAI(const _float& fTimer)
{
	// 부품 생성
	CSequence* pSQJump = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQJump, nullptr);

	CJump* pTskJump = dynamic_cast<CJump*>(Engine::Clone_Proto(L"TSK_Jump", this));
	NULL_CHECK_RETURN(pTskJump, nullptr);

	// 부품 초기설정
	pTskJump->Set_Timer(fTimer);

	// 부품 조립
	FAILED_CHECK_RETURN(pSQJump->Add_Component(ID_UPDATE, L"TSK_Jump", pTskJump), nullptr);

	return pSQJump;
}

CSequence * CMonster::Make_DBJumpAI(const _float & fTimer)
{
	// 부품 생성
	CSequence* pSQJump = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQJump, nullptr);

	CJump* pTskJump1 = dynamic_cast<CJump*>(Engine::Clone_Proto(L"TSK_Jump", this));
	NULL_CHECK_RETURN(pTskJump1, nullptr);
	CJump* pTskJump2 = dynamic_cast<CJump*>(Engine::Clone_Proto(L"TSK_Jump", this));
	NULL_CHECK_RETURN(pTskJump2, nullptr);

	// 부품 초기설정
	pTskJump1->Set_Timer(fTimer);
	pTskJump2->Set_Timer(0.f);

	// 부품 조립
	FAILED_CHECK_RETURN(pSQJump->Add_Component(ID_UPDATE, L"TSK_BackJump", pTskJump1), nullptr);
	FAILED_CHECK_RETURN(pSQJump->Add_Component(ID_UPDATE, L"TSK_BackJump", pTskJump2), nullptr);

	return pSQJump;
}

CSequence * CMonster::Make_DBBackJumpAI(const _float & fTimer)
{
	// 부품 생성
	CSequence* pSQJump = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQJump, nullptr);

	CBackJump* pTskJump1 = dynamic_cast<CBackJump*>(Engine::Clone_Proto(L"TSK_BackJump", this));
	NULL_CHECK_RETURN(pTskJump1, nullptr);
	CBackJump* pTskJump2 = dynamic_cast<CBackJump*>(Engine::Clone_Proto(L"TSK_BackJump", this));
	NULL_CHECK_RETURN(pTskJump2, nullptr);

	// 부품 초기설정
	pTskJump1->Set_Timer(fTimer);
	pTskJump2->Set_Timer(0.f);

	// 부품 조립
	FAILED_CHECK_RETURN(pSQJump->Add_Component(ID_UPDATE, L"TSK_Jump", pTskJump1), nullptr);
	FAILED_CHECK_RETURN(pSQJump->Add_Component(ID_UPDATE, L"TSK_Jump", pTskJump2), nullptr);

	return pSQJump;
}

CSequence * CMonster::Make_LeapJumpAI(const _float & fTimer)
{
	// 부품 생성
	CSequence* pSQLeapJump = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQLeapJump, nullptr);

	CLeapJump* pTskLeapJump = dynamic_cast<CLeapJump*>(Engine::Clone_Proto(L"TSK_LeapJump", this));
	NULL_CHECK_RETURN(pTskLeapJump, nullptr);

	// 부품 초기설정
	pTskLeapJump->Set_Timer(fTimer);

	// 부품 조립
	FAILED_CHECK_RETURN(pSQLeapJump->Add_Component(ID_UPDATE, L"TSK_LeapJump", pTskLeapJump), nullptr);

	return pSQLeapJump;
}

CSequence * CMonster::Make_JumpToPlayer()
{
	// 부품 생성
	CSequence* pSQJump = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQJump, nullptr);

	CLookAtTarget* pTskLookAt = dynamic_cast<CLookAtTarget*>(Engine::Clone_Proto(L"TSK_LookAtTarget", this));
	NULL_CHECK_RETURN(pTskLookAt, nullptr);
	CLeapJump* pTskLeapJump = dynamic_cast<CLeapJump*>(Engine::Clone_Proto(L"TSK_LeapJump", this));
	NULL_CHECK_RETURN(pTskLeapJump, nullptr);

	// 부품 초기설정

	// 부품 조립
	FAILED_CHECK_RETURN(pSQJump->Add_Component(ID_UPDATE, L"TSK_LookAtPlayer", pTskLookAt), nullptr);
	FAILED_CHECK_RETURN(pSQJump->Add_Component(ID_UPDATE, L"TSK_LeapJump", pTskLeapJump), nullptr);

	return pSQJump;
}

CSequence * CMonster::Make_RushAI()
{
	// 부품 생성
	CSequence* pSQRush = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQRush, nullptr);

	CLookAtTarget* pTskLookatTarget = dynamic_cast<CLookAtTarget*>(Engine::Clone_Proto(L"TSK_LookAtTarget", this));
	NULL_CHECK_RETURN(pTskLookatTarget, nullptr);
	CRush* pTskRush = dynamic_cast<CRush*>(Engine::Clone_Proto(L"TSK_Rush", this));
	NULL_CHECK_RETURN(pTskRush, nullptr);

	// 부품 초기설정

	// 부품 조립
	FAILED_CHECK_RETURN(pSQRush->Add_Component(ID_UPDATE, L"TSK_LookAtTarget", pTskLookatTarget), nullptr);
	FAILED_CHECK_RETURN(pSQRush->Add_Component(ID_UPDATE, L"TSK_Rush", pTskRush), nullptr);

	return pSQRush;
}

CSequence* CMonster::Make_BossPattern1(const _float& fCoolTime)
{
	// 부품 생성
	CSequence* pSQPattern1 = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQPattern1, nullptr);

	// 부품 초기설정

	// 부품 조립
	FAILED_CHECK_RETURN(pSQPattern1->Add_Component(ID_UPDATE, L"SQ_DBJump", Make_DBJumpAI(fCoolTime)), nullptr);
	FAILED_CHECK_RETURN(pSQPattern1->Add_Component(ID_UPDATE, L"SQ_Rush", Make_RushAI()), nullptr);
	FAILED_CHECK_RETURN(pSQPattern1->Add_Component(ID_UPDATE, L"SQ_Jump", Make_JumpAI()), nullptr);

	return pSQPattern1;
}

CSequence * CMonster::Make_BossPattern2(const _float & fCoolTime)
{
	// 부품 생성
	CSequence* pSQPattern1 = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQPattern1, nullptr);

	// 부품 초기설정

	// 부품 조립
	FAILED_CHECK_RETURN(pSQPattern1->Add_Component(ID_UPDATE, L"SQ_DBBackJump", Make_DBBackJumpAI(fCoolTime)), nullptr);

	for (_uint i = 0; i < 5; ++i)
	{
		FAILED_CHECK_RETURN(pSQPattern1->Add_Component(ID_UPDATE, L"SQ_Rush", Make_RushAI()), nullptr);
		FAILED_CHECK_RETURN(pSQPattern1->Add_Component(ID_UPDATE, L"SQ_JumpToPlayer", Make_JumpToPlayer()), nullptr);
	}
	FAILED_CHECK_RETURN(pSQPattern1->Add_Component(ID_UPDATE, L"SQ_Jump", Make_JumpAI()), nullptr);

	return pSQPattern1;
}

HRESULT CMonster::Set_PatrolAndFollow_AI()
{
	CSelector* pSLRootAI = dynamic_cast<CSelector*>(Engine::Clone_Proto(L"Selector", this));
	NULL_CHECK_RETURN(pSLRootAI, E_FAIL);

	// 부품 조립
	FAILED_CHECK_RETURN(m_pRoot->Add_Component(ID_UPDATE, L"SL_RootAI", pSLRootAI));

	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Follow", Make_Follow_AI()));
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Patrol", Make_Patrol_AI()));

	return S_OK;
}

HRESULT CMonster::Set_PAF_JumpAI()
{
	CSelector* pSLRootAI = dynamic_cast<CSelector*>(Engine::Clone_Proto(L"Selector", this));
	NULL_CHECK_RETURN(pSLRootAI, E_FAIL);

	// 부품 조립
	FAILED_CHECK_RETURN(m_pRoot->Add_Component(ID_UPDATE, L"SL_RootAI", pSLRootAI));

	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Follow", Make_Follow_AI(4.f)));
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Jump", Make_JumpAI(3.f)));
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Patrol", Make_Patrol_AI()));

	return S_OK;
}

HRESULT CMonster::Set_PAF_DBJumpAI()
{
	CSelector* pSLRootAI = dynamic_cast<CSelector*>(Engine::Clone_Proto(L"Selector", this));
	NULL_CHECK_RETURN(pSLRootAI, E_FAIL);

	// 부품 조립
	FAILED_CHECK_RETURN(m_pRoot->Add_Component(ID_UPDATE, L"SL_RootAI", pSLRootAI));

	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Follow", Make_Follow_AI(4.f)));
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_DBJump", Make_DBJumpAI(3.f)));
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Patrol", Make_Patrol_AI()));

	return S_OK;
}

HRESULT CMonster::Set_PAF_LeapJumpAI()
{
	CSelector* pSLRootAI = dynamic_cast<CSelector*>(Engine::Clone_Proto(L"Selector", this));
	NULL_CHECK_RETURN(pSLRootAI, E_FAIL);

	CWait* pTaskWait = dynamic_cast<CWait*>(Engine::Clone_Proto(L"TSK_Wait", this));
	NULL_CHECK_RETURN(pTaskWait, E_FAIL);

	// 부품 초기설정
	pTaskWait->Set_Timer(0.2f);

	// 부품 조립
	FAILED_CHECK_RETURN(m_pRoot->Add_Component(ID_UPDATE, L"SL_RootAI", pSLRootAI));

	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Follow", Make_Follow_AI(4.f)), E_FAIL);
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"TSK_Wait", pTaskWait), E_FAIL);
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_LeapJump", Make_LeapJumpAI(3.f)), E_FAIL);
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Patrol", Make_Patrol_AI()), E_FAIL);

	return S_OK;
}

HRESULT CMonster::Set_TurretAI()
{
	// 부품 생성
	CSequence* pSQChaseAtk = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQChaseAtk, E_FAIL);

	CRotToFace* pTskRot = dynamic_cast<CRotToFace*>(Engine::Clone_Proto(L"TSK_Rot", this));
	NULL_CHECK_RETURN(pTskRot, E_FAIL);
	CAttack* pTskAttack = dynamic_cast<CAttack*>(Engine::Clone_Proto(L"TSK_Attack", this));
	NULL_CHECK_RETURN(pTskAttack, E_FAIL);

	CIsRangeInPlayer* pDecIsRangeInPlayer = dynamic_cast<CIsRangeInPlayer*>(Engine::Clone_Proto(L"DEC_IsRangeInPlayer", this));
	NULL_CHECK_RETURN(pDecIsRangeInPlayer, E_FAIL);

	// 부품 초기설정
	pTskAttack->Set_Timer(1.f);

	// 부품 조립
	FAILED_CHECK_RETURN(m_pRoot->Add_Component(ID_UPDATE, L"SQ_ChaseAtk", pSQChaseAtk), E_FAIL);

	FAILED_CHECK_RETURN(pSQChaseAtk->Add_Decorator(pDecIsRangeInPlayer), E_FAIL);

	FAILED_CHECK_RETURN(pSQChaseAtk->Add_Component(ID_UPDATE, L"TSK_Rot", pTskRot), E_FAIL);
	FAILED_CHECK_RETURN(pSQChaseAtk->Add_Component(ID_UPDATE, L"TSK_Attack", pTskAttack), E_FAIL);

	return S_OK;
}

HRESULT CMonster::Set_Boss1_AI()
{
	// 부품 생성
	CSelector* pSLRootAI = dynamic_cast<CSelector*>(Engine::Clone_Proto(L"Selector", this));
	NULL_CHECK_RETURN(pSLRootAI, E_FAIL);

	// 부품 초기설정

	// 부품 조립
	FAILED_CHECK_RETURN(m_pRoot->Add_Component(ID_UPDATE, L"SL_RootAI", pSLRootAI), E_FAIL);

	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Follow", Make_Follow_AI(6.f)), E_FAIL);
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Pattern1", Make_BossPattern1()), E_FAIL);
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Pattern2", Make_BossPattern2()), E_FAIL);

	return S_OK;
}

HRESULT CMonster::Set_Boss2_AI()
{
	// 부품 생성
	CSelector* pSLRootAI = dynamic_cast<CSelector*>(Engine::Clone_Proto(L"Selector", this));
	NULL_CHECK_RETURN(pSLRootAI, E_FAIL);

	// 부품 초기설정


	// 부품 조립
	FAILED_CHECK_RETURN(m_pRoot->Add_Component(ID_UPDATE, L"SL_RootAI", pSLRootAI), E_FAIL);

	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Follow", Make_Follow_AI(6.f)), E_FAIL);
	FAILED_CHECK_RETURN(pSLRootAI->Add_Component(ID_UPDATE, L"SQ_Pattern1", Make_BossPattern1()), E_FAIL);

	return S_OK;
}

HRESULT CMonster::Init_AI_Behaviours()
{
	// 조립된 트리 전체 초기화
	FAILED_CHECK_RETURN(dynamic_cast<CRoot*>(m_pRoot)->Ready_Behavior(), E_FAIL);

	// 루트의 블랙보드에 자료형 채우기
	FAILED_CHECK_RETURN(m_pRoot->m_pBlackBoard->Add_Type(L"fSpeed", m_fSpeed), E_FAIL);

	return S_OK;
}


