#include "stdafx.h"
#include "AIRoot.h"
#include "ChasePlayer.h"

#include "Export_Utility.h"

CAIRoot::CAIRoot(LPDIRECT3DDEVICE9 pGraphicDev)
	:CSelector(pGraphicDev)
{
}

CAIRoot::CAIRoot(const CAIRoot & rhs)
	:CSelector(rhs)
{
}

CAIRoot::~CAIRoot()
{
}

HRESULT CAIRoot::Ready_Behavior()
{
	__super::Ready_Composite();

	return S_OK;
}

_int CAIRoot::Update_Component(const _float & fTimeDelta)
{
	return __super::Update_Component(fTimeDelta);
}

void CAIRoot::LateUpdate_Component(void)
{
	__super::LateUpdate_Component();
}

void CAIRoot::Render_Component(void)
{
	__super::Render_Component();
}

CAIRoot * CAIRoot::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CAIRoot* pInstance = new CAIRoot(pGraphicDev);

	if (FAILED(pInstance->Ready_Behavior()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CAIRoot::Clone(void)
{
	return new CAIRoot(*this);
}

void CAIRoot::Free()
{
	__super::Free();
}
