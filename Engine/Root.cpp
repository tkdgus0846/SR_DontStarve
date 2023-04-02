#include "stdafx.h"
#include "Root.h"
#include "AIRoot.h"

#include "Export_Utility.h"

CRoot::CRoot(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBehavior(pGraphicDev)
{
}

CRoot::CRoot(const CRoot & rhs)
	:CBehavior(rhs)
{
}

CRoot::~CRoot()
{
}

HRESULT CRoot::Ready_Behavior(void)
{
	m_pBlackBoard = new CBlackBoard;

	m_pBlackBoard->Add_Type(L"fSpeed", 10.f);

	__super::Ready_Composite();
	return S_OK;
}

_int CRoot::Update_Component(const _float & fTimeDelta)
{
	__super::Update_Component(fTimeDelta);
	return 0;
}

void CRoot::LateUpdate_Component(void)
{
	__super::LateUpdate_Component();
}

void CRoot::Render_Component(void)
{
	__super::Render_Component();
}

CRoot * CRoot::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRoot* pInstance = new CRoot(pGraphicDev);

	if (FAILED(pInstance->Ready_Behavior()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CRoot::Clone(void)
{
	return new CRoot(*this);
}

void CRoot::Free()
{
	Safe_Delete(m_pBlackBoard);
	__super::Free();
}
