#include "stdafx.h"
#include "Component.h"
#include "GameObject.h"


CComponent::CComponent() 
	: m_pGraphicDev(nullptr)
	, m_pGameObject(nullptr)
	, m_bClone(false)
{
}

CComponent::CComponent(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
	, m_pGameObject(nullptr)
	, m_bClone(false)
{
	m_pGraphicDev->AddRef();
}

CComponent::CComponent(const CComponent & rhs)
	: m_pGraphicDev(rhs.m_pGraphicDev)
	, m_pGameObject(rhs.m_pGameObject)
	, m_bClone(true)
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

// Composite

CComposite::CComposite()
	:CComponent()
{
}

CComposite::CComposite(LPDIRECT3DDEVICE9 pGraphicDev)
	: CComponent(pGraphicDev)
	, m_iterCurComponent(m_VecComponents[ID_DYNAMIC].begin())
	, m_iterPreComponent(m_VecComponents[ID_DYNAMIC].begin())
{
}

CComposite::CComposite(const CComposite & rhs)
	: CComponent(rhs)
	, m_iterCurComponent(rhs.m_iterCurComponent)
	, m_iterPreComponent(rhs.m_iterPreComponent)
{
}

CComposite::~CComposite()
{
}

HRESULT CComposite::Ready_Composite(void)
{
	m_iterCurComponent = m_VecComponents[ID_DYNAMIC].begin();
	m_iterPreComponent = m_VecComponents[ID_DYNAMIC].begin();

	return S_OK;
}

_int CComposite::Update_Component(const _float & fTimeDelta)
{
	for (auto& iter : m_VecComponents[ID_DYNAMIC])
	{
		_int iResult = iter.pComponent->Update_Component(fTimeDelta);
	}
	return 0;
}

void CComposite::LateUpdate_Component(void)
{
	for (auto& iter : m_VecComponents[ID_DYNAMIC])
	{
		iter.pComponent->LateUpdate_Component();
	}
}

void CComposite::Render_Component(void)
{
	for (auto& iter : m_VecComponents[ID_DYNAMIC])
	{
		iter.pComponent->Render_Component();
	}
}

HRESULT CComposite::Add_Component(COMPONENTID eID, 
									const _int & iPriority, 
									const _tchar * pComponentTag, 
									CComponent * pComponent)
{
	for (auto iter : m_VecComponents[eID])
	{
		if (iter.iPriority == iPriority)
			return E_FAIL;
	}

	m_VecComponents[eID].push_back({ iPriority, pComponentTag, pComponent });

	sort(m_VecComponents[eID].begin(), m_VecComponents[eID].end(), [](auto Src, auto Dest)->bool
	{
		return Src.iPriority < Dest.iPriority;
	});
}

void Engine::CComposite::Free(void)
{
	for (int i = 0; i < ID_END; i++)
	{
		for (auto& comp : m_VecComponents[i])
		{
			Safe_Release(comp.pComponent);
		}
	}

	__super::Free();
}