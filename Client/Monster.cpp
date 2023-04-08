#include "stdafx.h"
#include "Monster.h"

#include "Export_Function.h"
#include "MonoBehaviors.h"

CMonster::CMonster(LPDIRECT3DDEVICE9 pGraphicDev)
	: CCreature(pGraphicDev), m_fSpeed(0.f)
{
}

CMonster::~CMonster()
{
}

HRESULT CMonster::Ready_GameObject(void)
{
	m_fSpeed = 10.f;

	HRESULT result = __super::Ready_GameObject();

	return result;
}

_int CMonster::Update_GameObject(const _float& fTimeDelta)
{
	_matrix view;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &view);

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
	__super::Render_GameObject();
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

// AI	구현부
HRESULT CMonster::Set_PatrolAndFollow_AI()
{
	// 부품 생성
	CComponent* pRoot = dynamic_cast<CRoot*>(Engine::Clone_Proto(L"Root", this));
	NULL_CHECK_RETURN(pRoot, E_FAIL);

	CComponent* pSelector = dynamic_cast<CSelector*>(Engine::Clone_Proto(L"Selector", this));
	NULL_CHECK_RETURN(pSelector, E_FAIL);

	CComponent* pSQChase = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQChase, E_FAIL);
	CComponent* pSQPatrol = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQPatrol, E_FAIL);
	
	CComponent* pTaskMovePlayer = dynamic_cast<CMoveLook*>(Engine::Clone_Proto(L"TSK_Move", this));
	NULL_CHECK_RETURN(pTaskMovePlayer, E_FAIL);
	CComponent* pTaskMovePatrol = dynamic_cast<CMoveLook*>(Engine::Clone_Proto(L"TSK_Move", this));
	NULL_CHECK_RETURN(pTaskMovePatrol, E_FAIL);
	CComponent* pTaskRot = dynamic_cast<CRotToFace*>(Engine::Clone_Proto(L"TSK_Rot", this));
	NULL_CHECK_RETURN(pTaskRot, E_FAIL);
	CComponent* pTaskRandomLook = dynamic_cast<CRandomLook*>(Engine::Clone_Proto(L"TSK_RandomLook", this));
	NULL_CHECK_RETURN(pTaskRandomLook, E_FAIL);
	CComponent* pTaskWait = dynamic_cast<CWait*>(Engine::Clone_Proto(L"TSK_Wait", this));
	NULL_CHECK_RETURN(pTaskWait, E_FAIL);

	CComponent* pDecRangeCheck = dynamic_cast<CRangeCheck*>(Engine::Clone_Proto(L"DEC_RangeCheck", this));
	NULL_CHECK_RETURN(pDecRangeCheck, E_FAIL);

	// 부품 초기설정
	dynamic_cast<CWait*>(pTaskWait)->Set_Limit(1.f);
	dynamic_cast<CMoveLook*>(pTaskMovePatrol)->Set_MoveTimer(0.5f);

	// 부품 조립
	FAILED_CHECK_RETURN(dynamic_cast<CRoot*>(pRoot)->Add_Component(ID_UPDATE, 1, L"SL_AIRoot", pSelector), E_FAIL);

	FAILED_CHECK_RETURN(dynamic_cast<CSelector*>(pSelector)->Add_Component(ID_UPDATE, 1, L"SQ_Chase", pSQChase), E_FAIL);
	FAILED_CHECK_RETURN(dynamic_cast<CSelector*>(pSelector)->Add_Component(ID_UPDATE, 2, L"SQ_Patrol", pSQPatrol), E_FAIL);
	
	FAILED_CHECK_RETURN(dynamic_cast<CSequence*>(pSQChase)->Add_Decorator(pDecRangeCheck), E_FAIL);

	FAILED_CHECK_RETURN(dynamic_cast<CSequence*>(pSQChase)->Add_Component(ID_UPDATE, 1, L"TSK_Rot", pTaskRot), E_FAIL);
	FAILED_CHECK_RETURN(dynamic_cast<CSequence*>(pSQChase)->Add_Component(ID_UPDATE, 2, L"TSK_MovePlayer", pTaskMovePlayer), E_FAIL);

	FAILED_CHECK_RETURN(dynamic_cast<CSequence*>(pSQPatrol)->Add_Component(ID_UPDATE, 1, L"TSK_RandomLook", pTaskRandomLook), E_FAIL);
	FAILED_CHECK_RETURN(dynamic_cast<CSequence*>(pSQPatrol)->Add_Component(ID_UPDATE, 2, L"TSK_MovePatrol", pTaskMovePatrol), E_FAIL);
	FAILED_CHECK_RETURN(dynamic_cast<CSequence*>(pSQPatrol)->Add_Component(ID_UPDATE, 3, L"TSK_Wait", pTaskWait), E_FAIL);

	// 조립된 트리 전체 초기화
	FAILED_CHECK_RETURN(dynamic_cast<CRoot*>(pRoot)->Ready_Behavior(), E_FAIL);

	// 루트의 블랙보드에 자료형 채우기
	FAILED_CHECK_RETURN(dynamic_cast<CRoot*>(pRoot)->m_pBlackBoard->Add_Type(L"fSpeed", m_fSpeed), E_FAIL);

	m_uMapComponent[ID_UPDATE].emplace(L"Root", pRoot);

	return S_OK;
}

HRESULT CMonster::Set_TurretAI()
{
	// 부품 생성
	CComponent* pRoot = dynamic_cast<CRoot*>(Engine::Clone_Proto(L"Root", this));
	NULL_CHECK_RETURN(pRoot, E_FAIL);

	CComponent* pSQChaseAtk = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQChaseAtk, E_FAIL);

	CComponent* pTaskRot = dynamic_cast<CRotToFace*>(Engine::Clone_Proto(L"TSK_Rot", this));
	NULL_CHECK_RETURN(pTaskRot, E_FAIL);
	CComponent* pTaskAttack = dynamic_cast<CAttack*>(Engine::Clone_Proto(L"TSK_Attack", this));
	NULL_CHECK_RETURN(pTaskAttack, E_FAIL);

	CComponent* pDecRangeCheck = dynamic_cast<CRangeCheck*>(Engine::Clone_Proto(L"DEC_RangeCheck", this));
	NULL_CHECK_RETURN(pDecRangeCheck, E_FAIL);

	// 부품 초기설정

	// 부품 조립
	FAILED_CHECK_RETURN(dynamic_cast<CRoot*>(pRoot)->Add_Component(ID_UPDATE, 1, L"SQ_ChaseAtk", pSQChaseAtk), E_FAIL);

	FAILED_CHECK_RETURN(dynamic_cast<CSequence*>(pSQChaseAtk)->Add_Decorator(pDecRangeCheck), E_FAIL);

	FAILED_CHECK_RETURN(dynamic_cast<CSequence*>(pSQChaseAtk)->Add_Component(ID_UPDATE, 1, L"TSK_Rot", pTaskRot), E_FAIL);
	FAILED_CHECK_RETURN(dynamic_cast<CSequence*>(pSQChaseAtk)->Add_Component(ID_UPDATE, 2, L"TSK_Attack", pTaskAttack), E_FAIL);

	// 조립된 트리 전체 초기화
	FAILED_CHECK_RETURN(dynamic_cast<CRoot*>(pRoot)->Ready_Behavior(), E_FAIL);

	// 루트의 블랙보드에 자료형 채우기
	FAILED_CHECK_RETURN(dynamic_cast<CRoot*>(pRoot)->m_pBlackBoard->Add_Type(L"fSpeed", m_fSpeed), E_FAIL);

	m_uMapComponent[ID_UPDATE].emplace(L"Root", pRoot);

	return S_OK;
}

