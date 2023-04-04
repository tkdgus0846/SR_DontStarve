#include "stdafx.h"
#include "RandomLook.h"

#include "Export_Utility.h"

CRandomLook::CRandomLook(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBehavior(pGraphicDev)
{
}

CRandomLook::CRandomLook(const CRandomLook & rhs)
	: CBehavior(rhs)
{
}

CRandomLook::~CRandomLook()
{
}

HRESULT CRandomLook::Ready_Behavior()
{
	return S_OK;
}

_int CRandomLook::Update_Component(const _float & fTimeDelta)
{
	_vec3 vRandomLook;
	_vec3 vMin(-180.f, -180.f, -180.f);
	_vec3 vMax(180.f, 180.f, 180.f);

	GetRandomVector(&vRandomLook, &vMin, &vMax);
	vRandomLook.Normalize();

	m_pGameObject->m_pTransform->m_vInfo[INFO_LOOK] = vRandomLook;

	_vec3 vLookPos = m_pGameObject->m_pTransform->m_vInfo[INFO_POS] +
		m_pGameObject->m_pTransform->m_vInfo[INFO_LOOK];

	m_pGameObject->m_pTransform->Set_Target(vLookPos);
	
	return BEHAVIOR_TRUE;
}

void CRandomLook::LateUpdate_Component(void)
{
	__super::LateUpdate_Component();
}

void CRandomLook::Render_Component(void)
{
	__super::Render_Component();
}

CRandomLook * CRandomLook::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRandomLook* pInstance = new CRandomLook(pGraphicDev);

	if (FAILED(pInstance->Ready_Behavior()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CRandomLook::Clone(void)
{
	return new CRandomLook(*this);
}

void CRandomLook::Free()
{
	__super::Free();
}
