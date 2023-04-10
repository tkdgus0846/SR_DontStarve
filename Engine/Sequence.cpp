#include "stdafx.h"
#include "Sequence.h"

#include "Export_Utility.h"

CSequence::CSequence(LPDIRECT3DDEVICE9 pGraphicDev)
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

HRESULT CSequence::Ready_Behavior()
{
	for (_uint i = 0; i < ID_END; ++i)
	{
		for (auto iter : m_VecComponents[i])
		{
			dynamic_cast<CBehavior*>(iter.pComponent)->m_pBlackBoard = m_pBlackBoard;
			dynamic_cast<CBehavior*>(iter.pComponent)->Ready_Behavior();
		}
	}

	__super::Ready_Composite();

	return S_OK;
}

_int CSequence::Update_Component(const _float & fTimeDelta)
{
	if (0 == m_VecComponents[ID_UPDATE].size())
		return BEHAVIOR_FALSE;

	if (BEHAVIOR_FALSE == update_Decorator(fTimeDelta))
		return BEHAVIOR_FALSE;

	_int iResult = m_iterCurComponent->pComponent->Update_Component(fTimeDelta);

	switch (iResult)
	{
	case RUNNING:
		return RUNNING;

	case BEHAVIOR_TRUE:
		++m_iterPreComponent;

		if (m_iterPreComponent == m_VecComponents[ID_UPDATE].end())
		{
			m_iterPreComponent = m_VecComponents[ID_UPDATE].begin();
			return BEHAVIOR_TRUE;
		}
		else
			return RUNNING;

	case BEHAVIOR_FALSE:
		m_iterPreComponent = m_VecComponents[ID_UPDATE].begin();
		return BEHAVIOR_FALSE;
	}

	return BEHAVIOR_FALSE;
}

void CSequence::LateUpdate_Component(void)
{
	if (0 == m_VecComponents[ID_UPDATE].size())
		return;

	m_iterCurComponent->pComponent->LateUpdate_Component();

	if (m_iterCurComponent != m_iterPreComponent)
		m_iterCurComponent = m_iterPreComponent;
}

void CSequence::Render_Component(void)
{
	__super::Render_Component();
}

CSequence * CSequence::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSequence* pInstance = new CSequence(pGraphicDev);

	if (!pInstance)
		return nullptr;

	return pInstance;
}

CComponent * CSequence::Clone(void)
{
	return new CSequence(*this);
}

void CSequence::Free()
{
	__super::Free();
}
