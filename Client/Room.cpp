#include "stdafx.h"
#include "Room.h"

#include "Export_Function.h"
CRoom::CRoom(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev), m_fVtxCntX(0.f), 
	m_fVtxCntZ(0.f), m_fVtxItv(0.f)
{
}


CRoom::~CRoom()
{
}

HRESULT CRoom::Ready_GameObject(const _float& fVtxCntX, const _float& fVtxCntZ, const _float& fVtxItv)
{
	m_fVtxItv = fVtxItv;
	m_fVtxCntX = fVtxCntX;
	m_fVtxCntZ = fVtxCntZ;

	HRESULT result = __super::Ready_GameObject();
	FAILED_CHECK_RETURN(CreateSubset(), E_FAIL);

	return result;
}

_int CRoom::Update_GameObject(const _float& fTimeDelta)
{
	__super::Update_GameObject(fTimeDelta);
	Update_Subset(fTimeDelta);
	
	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return 0;
}

void CRoom::LateUpdate_GameObject(void)
{
	// 룸 특성상 트랜스폼 외엔 안쓸거같아서 일단 주석처리
	//__super::LateUpdate_GameObject();
	LateUpdate_SubSet();
}

void CRoom::Render_GameObject(void)
{
	// 룸 특성상 트랜스폼 외엔 안쓸거같아서 일단 주석처리
	//__super::Render_GameObject();
	Render_SubSet();
}

void CRoom::Update_Subset(const _float& fTimeDelta)
{
	__super::Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	m_pFloor->Update_GameObject(fTimeDelta);
	for (auto& iter : m_apWall)
		iter->Update_GameObject(fTimeDelta);
}

void CRoom::LateUpdate_SubSet()
{
	m_pFloor->LateUpdate_GameObject();
	for (auto& iter : m_apWall)
		iter->LateUpdate_GameObject();
}

void CRoom::Render_SubSet()
{
	m_pFloor->Render_GameObject();
	for (auto& iter : m_apWall)
		iter->Render_GameObject();

}

HRESULT CRoom::CreateSubset()
{
	// 바닥 생성
	m_pFloor = CFloor::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(m_pFloor, E_FAIL);

	// 벽 4면 생성
	for (auto& iter : m_apWall)
		iter = CWall::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(m_apWall[0], E_FAIL);

	return S_OK;
}

void CRoom::FloorSubSet()
{
	// 바닥 위치 조정
	_vec3 vPos;
	m_pTransform->Get_Info(INFO_POS, &vPos);

	m_pFloor->m_pTransform->Set_Pos(vPos);
}

void CRoom::PlaceSubSet()	
{
	// 벽 위치 조정
	_vec3 vPos;
	float fLengthX = (m_fVtxCntX - 1) * m_fVtxItv;
	float fLengthZ = (m_fVtxCntZ - 1) * m_fVtxItv;
	m_pTransform->Get_Info(INFO_POS, &vPos);

	m_apWall[0]->m_pTransform->Set_Pos(vPos);
	m_apWall[1]->m_pTransform->Set_Pos(vPos.x, vPos.y, vPos.z + fLengthZ);
	m_apWall[2]->m_pTransform->Set_Pos(vPos.x + fLengthX, vPos.y, vPos.z + fLengthZ);
	m_apWall[3]->m_pTransform->Set_Pos(vPos.x + fLengthX, vPos.y, vPos.z);

	m_apWall[1]->m_pTransform->Set_Target({ vPos.x + fLengthX, vPos.y, vPos.z + fLengthZ });
	m_apWall[2]->m_pTransform->Set_Target({ vPos.x + fLengthX, vPos.y, vPos.z });
	m_apWall[3]->m_pTransform->Set_Target(vPos);
}

HRESULT CRoom::Add_Component(void)
{
	CComponent*		pComponent = nullptr;
	
	return S_OK;
}

CRoom* CRoom::Create(LPDIRECT3DDEVICE9 pGraphicDev,
	const _float& fVtxCntX, const _float& fVtxCntZ, const _float& fVtxItv)
{
	CRoom*		pInstance = new CRoom(pGraphicDev);
	
	if (FAILED(pInstance->Ready_GameObject(fVtxCntX, fVtxCntZ, fVtxItv)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CRoom::Free(void)
{
	Safe_Release(m_pFloor);

	for (auto& iter : m_apWall)
		Safe_Release(iter);
	
	__super::Free();
}

