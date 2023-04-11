#include "stdafx.h"
#include "Monster.h"

#include "Export_Function.h"
#include "MonoBehaviors.h"
#include "Player.h"

CMonster::CMonster(LPDIRECT3DDEVICE9 pGraphicDev)
	: CCreature(pGraphicDev), m_fSpeed(0.f)
	, m_pRoot(nullptr)
{
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

void CMonster::OnCollisionEnter(const Collision * collsion)
{
	__super::OnCollisionEnter(collsion);

	CPlayer* player = dynamic_cast<CPlayer*>(collsion->OtherGameObject);

	if (player && collsion->MyCollider == Get_Component(L"BodyCollider", ID_ALL))
	{
		player->Get_Damaged(Get_Attack());
	}
}

void CMonster::OnCollisionStay(const Collision * collision)
{
	__super::OnCollisionStay(collision);
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

// AI	������
HRESULT CMonster::Set_PatrolAndFollow_AI() 
{
	// ��ǰ ����
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

	// ��ǰ �ʱ⼳��
	dynamic_cast<CWait*>(pTaskWait)->Set_Timer(1.f);
	dynamic_cast<CMoveLook*>(pTaskMovePatrol)->Set_Timer(0.5f);

	// ��ǰ ����
	FAILED_CHECK_RETURN(m_pRoot->Add_Component(ID_UPDATE, 1, L"SL_AIRoot", pSelector), E_FAIL);

	FAILED_CHECK_RETURN(dynamic_cast<CSelector*>(pSelector)->Add_Component(ID_UPDATE, 1, L"SQ_Chase", pSQChase), E_FAIL);
	FAILED_CHECK_RETURN(dynamic_cast<CSelector*>(pSelector)->Add_Component(ID_UPDATE, 2, L"SQ_Patrol", pSQPatrol), E_FAIL);
	
	FAILED_CHECK_RETURN(dynamic_cast<CSequence*>(pSQChase)->Add_Decorator(pDecRangeCheck), E_FAIL);

	FAILED_CHECK_RETURN(dynamic_cast<CSequence*>(pSQChase)->Add_Component(ID_UPDATE, 1, L"TSK_Rot", pTaskRot), E_FAIL);
	FAILED_CHECK_RETURN(dynamic_cast<CSequence*>(pSQChase)->Add_Component(ID_UPDATE, 2, L"TSK_MovePlayer", pTaskMovePlayer), E_FAIL);

	FAILED_CHECK_RETURN(dynamic_cast<CSequence*>(pSQPatrol)->Add_Component(ID_UPDATE, 1, L"TSK_RandomLook", pTaskRandomLook), E_FAIL);
	FAILED_CHECK_RETURN(dynamic_cast<CSequence*>(pSQPatrol)->Add_Component(ID_UPDATE, 2, L"TSK_MovePatrol", pTaskMovePatrol), E_FAIL);
	FAILED_CHECK_RETURN(dynamic_cast<CSequence*>(pSQPatrol)->Add_Component(ID_UPDATE, 3, L"TSK_Wait", pTaskWait), E_FAIL);

	return S_OK;
}

HRESULT CMonster::Set_TurretAI()
{
	// ��ǰ ����
	CComponent* pSQChaseAtk = dynamic_cast<CSequence*>(Engine::Clone_Proto(L"Sequence", this));
	NULL_CHECK_RETURN(pSQChaseAtk, E_FAIL);

	CComponent* pTaskRot = dynamic_cast<CRotToFace*>(Engine::Clone_Proto(L"TSK_Rot", this));
	NULL_CHECK_RETURN(pTaskRot, E_FAIL);
	CComponent* pTaskAttack = dynamic_cast<CAttack*>(Engine::Clone_Proto(L"TSK_Attack", this));
	NULL_CHECK_RETURN(pTaskAttack, E_FAIL);

	CComponent* pDecRangeCheck = dynamic_cast<CRangeCheck*>(Engine::Clone_Proto(L"DEC_RangeCheck", this));
	NULL_CHECK_RETURN(pDecRangeCheck, E_FAIL);

	// ��ǰ �ʱ⼳��

	// ��ǰ ����
	FAILED_CHECK_RETURN(m_pRoot->Add_Component(ID_UPDATE, 1, L"SQ_ChaseAtk", pSQChaseAtk), E_FAIL);

	FAILED_CHECK_RETURN(dynamic_cast<CSequence*>(pSQChaseAtk)->Add_Decorator(pDecRangeCheck), E_FAIL);

	FAILED_CHECK_RETURN(dynamic_cast<CSequence*>(pSQChaseAtk)->Add_Component(ID_UPDATE, 1, L"TSK_Rot", pTaskRot), E_FAIL);
	FAILED_CHECK_RETURN(dynamic_cast<CSequence*>(pSQChaseAtk)->Add_Component(ID_UPDATE, 2, L"TSK_Attack", pTaskAttack), E_FAIL);

	return S_OK;
}

HRESULT CMonster::Set_PAF_JumpAI()
{
	Set_PatrolAndFollow_AI();

	// ��ǰ ����
	CComponent* pTskJump = dynamic_cast<CJump*>(Engine::Clone_Proto(L"TSK_Jump", this));
	NULL_CHECK_RETURN(pTskJump, E_FAIL);

	// ������ �����ߴ� ������ ������
	CSelector* pSelector = dynamic_cast<CSelector*>(m_pRoot->Get_Component(L"SL_AIRoot", ID_UPDATE));
	CSequence* pSQChase = dynamic_cast<CSequence*>(pSelector->Get_Component(L"SQ_Chase", ID_UPDATE));

	// ��ǰ �ʱ⼳��
	dynamic_cast<CJump*>(pTskJump)->Set_Timer(4.f);

	// ��ǰ ����
	FAILED_CHECK_RETURN(dynamic_cast<CSequence*>(pSQChase)->Add_Component(ID_UPDATE, 3, L"TSK_Jump", pTskJump));
	
	return S_OK;
}

HRESULT CMonster::Init_AI_Behaviours()
{
	// ������ Ʈ�� ��ü �ʱ�ȭ
	FAILED_CHECK_RETURN(dynamic_cast<CRoot*>(m_pRoot)->Ready_Behavior(), E_FAIL);

	// ��Ʈ�� �����忡 �ڷ��� ä���
	FAILED_CHECK_RETURN(m_pRoot->m_pBlackBoard->Add_Type(L"fSpeed", m_fSpeed), E_FAIL);

	return E_NOTIMPL;
}


CGameObject * MonsterFactory::CreateMonster(const _tchar * tag)
{
		//if (_tcscmp(tag, _T("Zombie")) == 0) {
		//	return nullptr;// new Zombie();
		//}
		//else if (_tcscmp(tag, _T("Skeleton")) == 0) {
		//	return nullptr;// new Skeleton();
		//}
		//// ���⿡ �� ���� ���� Ŭ������ �߰��� �� �ֽ��ϴ�.
		//return nullptr;
	return nullptr;
}
