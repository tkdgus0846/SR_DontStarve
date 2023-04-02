#include "stdafx.h"
#include "Selector.h"

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

_int CSelector::Update_Component(const _float & fTimeDelta)
{
	if (0 == m_VecComponents[ID_DYNAMIC].size())
		return 0;

	_int iResult = m_iterCurComponent->pComponent->Update_Component(fTimeDelta);

	switch (iResult)
	{
	case RUNNING:
		return RUNNING;

	case BEHAVIOR_TRUE:
		m_iterPreComponent = m_VecComponents[ID_DYNAMIC].begin();
		return BEHAVIOR_FALSE;

	case BEHAVIOR_FALSE:
		++m_iterPreComponent;

		if (m_iterPreComponent == m_VecComponents[ID_DYNAMIC].end())
		{
			m_iterPreComponent = m_VecComponents[ID_DYNAMIC].begin();
			return BEHAVIOR_TRUE;
		}
		else
			return RUNNING;
	}
}

void CSelector::LateUpdate_Component(void)
{
	if (0 == m_VecComponents[ID_DYNAMIC].size() 
		|| m_iterCurComponent == m_VecComponents[ID_DYNAMIC].end())
		return;

	m_iterCurComponent->pComponent->LateUpdate_Component();

	if (m_iterCurComponent != m_iterPreComponent)
		m_iterCurComponent = m_iterPreComponent;
}

void CSelector::Render_Component(void)
{
	__super::Render_Component();
}

void CSelector::Free()
{
	__super::Free();
}
