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

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());

	__super::Render_GameObject();

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

HRESULT CMonster::Add_Component(void)
{
	CComponent*		pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CTriCol*>(Engine::Clone_Proto(L"TriCol",this));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"TriCol", pComponent });

	pComponent = m_pTransform = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Transform",this));
	NULL_CHECK_RETURN(m_pTransform, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"Transform", pComponent });

	pComponent = m_pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", this));
	NULL_CHECK_RETURN(m_pCollider, E_FAIL);
	m_uMapComponent[ID_DYNAMIC].insert({ L"Monster_Collider", pComponent });

	pComponent = m_pRoot = dynamic_cast<CRoot*>(Engine::Clone_Proto(L"Root", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_uMapComponent[ID_DYNAMIC].emplace(L"Root", pComponent);

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
	Safe_Release(m_pRoot);
	__super::Free();
}

