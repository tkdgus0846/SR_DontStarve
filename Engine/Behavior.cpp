#include "stdafx.h"
#include "Behavior.h"

#include "Export_Utility.h"

CBehavior::CBehavior(LPDIRECT3DDEVICE9 pGraphicDev)
	:CComposite(pGraphicDev), m_pBlackBoard(nullptr)
{
}

CBehavior::CBehavior(const CBehavior & rhs)
	:CComposite(rhs)
{
}

CBehavior::~CBehavior()
{
}

HRESULT CBehavior::Ready_Behavior()
{
	return __super::Ready_Composite();
}

_int CBehavior::Update_Component(const _float & fTimeDelta)
{
	return __super::Update_Component(fTimeDelta);
}

void CBehavior::LateUpdate_Component(void)
{
	__super::LateUpdate_Component();
}

void CBehavior::Render_Component(void)
{
	__super::Render_Component();
}

void CBehavior::Free()
{
	__super::Free();
}
