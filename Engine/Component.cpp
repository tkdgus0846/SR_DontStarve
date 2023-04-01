#include "stdafx.h"
#include "Component.h"
#include "GameObject.h"


CComponent::CComponent() 
	: m_pGraphicDev(nullptr), m_bClone(false)
{
}

CComponent::CComponent(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
	, m_bClone(false)
{
	m_pGraphicDev->AddRef();
}

CComponent::CComponent(const CComponent & rhs)
	: m_pGraphicDev(rhs.m_pGraphicDev),
	  m_bClone(true)
{
	m_pGraphicDev->AddRef();
}


CComponent::~CComponent()
{
}

Engine::CComponent* Engine::CComponent::Get_Component(const _tchar* pComponentTag, COMPONENTID eID)
{
	CComponent*		pComponent = m_pGameObject->Get_Component(pComponentTag, eID);
	NULL_CHECK_RETURN(pComponent, nullptr);

	return pComponent;
}

void CComponent::SetOwner(CGameObject * gameObject)
{
	m_pGameObject = gameObject;
}

void Engine::CComponent::Free(void)
{
	Safe_Release(m_pGraphicDev);
}

_int CComposite::Update_Component(const _float & fTimeDelta)
{
	for (auto& iter : m_VecComponents[ID_DYNAMIC])
	{
		FAILED_CHECK_RETURN(iter->Update_Component(fTimeDelta), E_FAIL);
	}	

	return 0;
}

void CComposite::LateUpdate_Component(void)
{
	for (auto& iter : m_VecComponents[ID_DYNAMIC])
	{
		iter->LateUpdate_Component();
	}
}

void CComposite::Render_Component(void)
{
	for (auto& iter : m_VecComponents[ID_DYNAMIC])
	{
		iter->Render_Component();
	}
}

void Engine::CComposite::Free(void)
{
	__super::Free();

	for (int i = 0; i < ID_END; i++)
	{
		for (auto& comp : m_VecComponents[i])
		{
			Safe_Release(comp);
		}
	}

	
}
