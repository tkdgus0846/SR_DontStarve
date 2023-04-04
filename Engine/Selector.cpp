#include "stdafx.h"
#include "Selector.h"

#include "Export_Utility.h"

CSelector::CSelector(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBehavior(pGraphicDev)
{
}

CSelector::CSelector(const CSelector & rhs)
	:CBehavior(rhs)
{
}

CSelector::~CSelector()
{
}

HRESULT CSelector::Ready_Behavior()
{
	for (_uint i = 0; i < ID_END; ++i)
	{
		for (auto iter : m_VecComponents[i])
		{
			dynamic_cast<CBehavior*>(iter.pComponent)->Set_BlackBoard(m_pBlackBoard);
			dynamic_cast<CBehavior*>(iter.pComponent)->Ready_Behavior();
		}
	}

	__super::Ready_Composite();

	return S_OK;
}

_int CSelector::Update_Component(const _float & fTimeDelta)
{
	if (0 == m_VecComponents[ID_UPDATE].size())
		return 0;

	_int iResult = m_iterCurComponent->pComponent->Update_Component(fTimeDelta);

	switch (iResult)
	{
	case RUNNING:
		return RUNNING;

	case BEHAVIOR_TRUE:
		m_iterPreComponent = m_VecComponents[ID_UPDATE].begin();
		return BEHAVIOR_FALSE;

	case BEHAVIOR_FALSE:
		++m_iterPreComponent;

		if (m_iterPreComponent == m_VecComponents[ID_UPDATE].end())
		{
			m_iterPreComponent = m_VecComponents[ID_UPDATE].begin();
			return BEHAVIOR_TRUE;
		}
		else
			return RUNNING;
	}
}

void CSelector::LateUpdate_Component(void)
{
	if (0 == m_VecComponents[ID_UPDATE].size())
		return;

	m_iterCurComponent->pComponent->LateUpdate_Component();

	if (m_iterCurComponent != m_iterPreComponent)
		m_iterCurComponent = m_iterPreComponent;
}

void CSelector::Render_Component(void)
{
	__super::Render_Component();
}

CSelector * CSelector::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSelector* pInstance = new CSelector(pGraphicDev);

	if (!pInstance)
		return nullptr;

	return pInstance;
}

CComponent * CSelector::Clone(void)
{
	return new CSelector(*this);
}

void CSelector::Free()
{
	__super::Free();
}
