#include "Evasion.h"

CEvasion::CEvasion(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBehavior(pGraphicDev)
{
}

CEvasion::CEvasion(const CEvasion & rhs)
	: CBehavior(rhs)
{
}

CEvasion::~CEvasion()
{
}

HRESULT CEvasion::Ready_Behavior()
{
	return S_OK;
}

_int CEvasion::Update_Component(const _float & fTimeDelta)
{
	return BEHAVIOR_TRUE;
}

void CEvasion::LateUpdate_Component(void)
{
}

void CEvasion::Render_Component(void)
{
}

CEvasion * CEvasion::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CEvasion* pInstance = new CEvasion(pGraphicDev);

	if (!pInstance)
		return nullptr;

	return pInstance;
}

CComponent * CEvasion::Clone(void)
{
	return new CEvasion(*this);
}

void CEvasion::Free()
{
	__super::Free();
}
