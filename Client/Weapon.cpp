#include "Weapon.h"
#include "Export_Function.h"

CWeapon::CWeapon(LPDIRECT3DDEVICE9 pGraphicDev) :
	CGameObject(pGraphicDev),
	m_fAccTime(0.f),
	m_bEnableShot(true),
	m_iDamage(1),
	m_fCycle(1.0f),
	m_bShooted(false)
{
	m_vOffsetTrans = { 1.f,1.f,0.f };
}

CWeapon::~CWeapon()
{
}

_int CWeapon::Update_GameObject(const _float& fTimeDelta)
{
	m_fAccTime += fTimeDelta;

	if (m_fAccTime >= m_fCycle && m_bShooted == true)
	{
		m_bEnableShot = true;
		m_fAccTime = 0.f;
		m_bShooted = false;
	}
	else
	{
		//m_bEnableShot = false;
		if (m_bShooted == false) m_fAccTime = 0.f;
	}

	m_pTransform->m_vInfo[INFO_POS] = 
		m_pOwnerTransform->m_vInfo[INFO_POS] + m_vOffsetTrans;
	
	
	/*m_pTransform->m_matWorld = m_pTransform->m_matWorld * (*m_pOwnerTransform->Get_WorldMatrixPointer());*/
	
	
	
	/*Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);*/
	
	//Add_RenderGroup(RENDER_ALPHA, this);
	return __super::Update_GameObject(fTimeDelta);
}

