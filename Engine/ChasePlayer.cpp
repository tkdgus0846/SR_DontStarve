#include "stdafx.h"
#include "ChasePlayer.h"

#include "Export_Utility.h"

CChasePlayer::CChasePlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	:CSequence(pGraphicDev)
{
}

CChasePlayer::CChasePlayer(const CChasePlayer & rhs)
	: CSequence(rhs)
{
}

CChasePlayer::~CChasePlayer()
{
}

HRESULT CChasePlayer::Ready_Behavior()
{
	__super::Ready_Composite();

	return S_OK;
}

_int CChasePlayer::Update_Component(const _float & fTimeDelta)
{
	return __super::Update_Component(fTimeDelta);
}

void CChasePlayer::LateUpdate_Component(void)
{
	__super::LateUpdate_Component();
}

void CChasePlayer::Render_Component(void)
{
	__super::Render_Component();
}

CChasePlayer * CChasePlayer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CChasePlayer* pInstance = new CChasePlayer(pGraphicDev);

	if (FAILED(pInstance->Ready_Behavior()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CChasePlayer::Clone(void)
{
	return new CChasePlayer(*this);
}

void CChasePlayer::Free()
{
	__super::Free();
}

