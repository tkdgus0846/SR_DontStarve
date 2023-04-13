#include "IsRangeInPlayer.h"

#include "Player.h"
#include "Export_Function.h"

CIsRangeInPlayer::CIsRangeInPlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBehavior(pGraphicDev)
{
}

CIsRangeInPlayer::CIsRangeInPlayer(const CIsRangeInPlayer & rhs)
	: CBehavior(rhs)
{
}

CIsRangeInPlayer::~CIsRangeInPlayer()
{
}

HRESULT CIsRangeInPlayer::Ready_Behavior()
{
	return S_OK;
}

_int CIsRangeInPlayer::Update_Component(const _float & fTimeDelta)
{
	CComponent* pComponent = m_pGameObject->Get_Component(L"Range", ID_ALL);

	for (auto iter : dynamic_cast<CCollider*>(pComponent)->Get_CollisionList())
	{
		if (nullptr != dynamic_cast<CPlayer*>(iter.second.OtherGameObject))
			return BEHAVIOR_SUCCES;
	}

	return BEHAVIOR_FAIL;
}

CIsRangeInPlayer * CIsRangeInPlayer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CIsRangeInPlayer* pInstance = new CIsRangeInPlayer(pGraphicDev);

	if (FAILED(pInstance->Ready_Behavior()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CIsRangeInPlayer::Clone(void)
{
	return new CIsRangeInPlayer(*this);
}

void CIsRangeInPlayer::Free()
{
	__super::Free();
}
