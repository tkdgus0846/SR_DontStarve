#include "stdafx.h"
#include "Monster.h"

#include "Export_Function.h"

CMonster::CMonster(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev), m_fSpeed(0.f)
{
}

CMonster::~CMonster()
{
}

HRESULT CMonster::Ready_GameObject(void)
{
	HRESULT result = __super::Ready_GameObject();

	m_fSpeed = 5.f;

	return result;
}

_int CMonster::Update_GameObject(const _float& fTimeDelta)
{
	__super::Update_GameObject(fTimeDelta);
	
	Engine::Add_RenderGroup(RENDER_NONALPHA, this);

	return 0;
}

void CMonster::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CMonster::Render_GameObject(void)
{
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	const _matrix* mat = m_pTransform->Get_WorldMatrixPointer();
	cout << mat->_41 << " | " << mat->_42 << " | " << mat->_43 << endl;
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());

	__super::Render_GameObject();

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

HRESULT CMonster::Add_Component(void)
{
	CComponent*		pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CTriCol*>(Engine::Clone_Proto(L"TriCol",this));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_uMapComponent[ID_DYNAMIC].insert({ L"TriCol", pComponent });

	pComponent = m_pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", this));
	NULL_CHECK_RETURN(m_pCollider, E_FAIL);
	m_uMapComponent[ID_DYNAMIC].insert({ L"Monster_Collider", pComponent });

	pComponent = m_pRange = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", this));
	NULL_CHECK_RETURN(m_pCollider, E_FAIL);
	m_uMapComponent[ID_DYNAMIC].insert({ L"Monster_Range", pComponent });
	m_pRange->Set_BoundingBox({ 15.f, 15.f, 15.f });

	FAILED_CHECK_RETURN(Set_Patrol_AI(), E_FAIL);

	return S_OK;
}

HRESULT CMonster::Set_Patrol_AI()
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

	// 부품 초기설정
	dynamic_cast<CWait*>(pTaskWait)->Set_Limit(1.f);
	dynamic_cast<CMoveLook*>(pTaskMovePatrol)->Set_MoveTimer(0.5f);

	// 부품 조립
	FAILED_CHECK_RETURN(dynamic_cast<CRoot*>(pRoot)->Add_Component(ID_DYNAMIC, 1, L"SL_AIRoot", pSelector), E_FAIL);

	FAILED_CHECK_RETURN(dynamic_cast<CSelector*>(pSelector)->Add_Component(ID_DYNAMIC, 1, L"SQ_Chase", pSQChase), E_FAIL);
	FAILED_CHECK_RETURN(dynamic_cast<CSelector*>(pSelector)->Add_Component(ID_DYNAMIC, 2, L"SQ_Patrol", pSQPatrol), E_FAIL);
	
	FAILED_CHECK_RETURN(dynamic_cast<CSequence*>(pSQChase)->Add_Component(ID_DYNAMIC, 2, L"TSK_Rot", pTaskRot), E_FAIL);
	FAILED_CHECK_RETURN(dynamic_cast<CSequence*>(pSQChase)->Add_Component(ID_DYNAMIC, 3, L"TSK_MovePlayer", pTaskMovePlayer), E_FAIL);

	FAILED_CHECK_RETURN(dynamic_cast<CSequence*>(pSQPatrol)->Add_Component(ID_DYNAMIC, 1, L"TSK_RandomLook", pTaskRandomLook), E_FAIL);
	FAILED_CHECK_RETURN(dynamic_cast<CSequence*>(pSQPatrol)->Add_Component(ID_DYNAMIC, 2, L"TSK_MovePatrol", pTaskMovePatrol), E_FAIL);
	FAILED_CHECK_RETURN(dynamic_cast<CSequence*>(pSQPatrol)->Add_Component(ID_DYNAMIC, 3, L"TSK_Wait", pTaskWait), E_FAIL);

	// 조립된 트리 전체 초기화
	FAILED_CHECK_RETURN(dynamic_cast<CRoot*>(pRoot)->Ready_Behavior(), E_FAIL);

	m_uMapComponent[ID_DYNAMIC].emplace(L"Root", pRoot);

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

