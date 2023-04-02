#include "stdafx.h"
#include "Sequence.h"


CSequence::CSequence(LPDIRECT3DDEVICE9 pGraphicDev)\
	:CBehavior(pGraphicDev)
{
}

CSequence::CSequence(const CSequence & rhs)
	:CBehavior(rhs)
{
}

CSequence::~CSequence()
{
}

_int CSequence::Update_Component(const _float & fTimeDelta)
{
	if (0 == m_VecComponents[ID_DYNAMIC].size())
		return 0;

	_int iResult = m_iterCurComponent->pComponent->Update_Component(fTimeDelta);

	switch (iResult)
	{
	case RUNNING:
		return RUNNING;

	case BEHAVIOR_TRUE:
		++m_iterPreComponent;

		if (m_iterPreComponent == m_VecComponents[ID_DYNAMIC].end())
		{
			m_iterPreComponent = m_VecComponents[ID_DYNAMIC].begin();
			return BEHAVIOR_TRUE;
		}

	case BEHAVIOR_FALSE:
		m_iterPreComponent = m_VecComponents[ID_DYNAMIC].begin();
		return BEHAVIOR_FALSE;
	}
}

void CSequence::LateUpdate_Component(void)
{
	if (0 == m_VecComponents[ID_DYNAMIC].size())
		return;

	m_iterCurComponent->pComponent->LateUpdate_Component();

	if (m_iterCurComponent != m_iterPreComponent)
		m_iterCurComponent = m_iterPreComponent;
}

void CSequence::Render_Component(void)
{
	__super::Render_Component();
}

void CSequence::Free()
{
	__super::Free();
}
