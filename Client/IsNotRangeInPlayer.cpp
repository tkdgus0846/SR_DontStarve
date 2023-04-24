#include "IsNotRangeInPlayer.h"

#include "Player.h"
#include "Export_Function.h"

CIsNotRangeInPlayer::CIsNotRangeInPlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBehavior(pGraphicDev)
{
}

CIsNotRangeInPlayer::CIsNotRangeInPlayer(const CIsNotRangeInPlayer & rhs)
	: CBehavior(rhs)
{
}

CIsNotRangeInPlayer::~CIsNotRangeInPlayer()
{
}

HRESULT CIsNotRangeInPlayer::Ready_Behavior()
{
	HRESULT result = __super::Ready_Behavior();

	return result;
}

_int CIsNotRangeInPlayer::Update_Component(const _float & fTimeDelta)
{
	CComponent* pComponent = m_pGameObject->Get_Component(L"Range", ID_ALL);

	for (auto iter : dynamic_cast<CCollider*>(pComponent)->Get_CollisionList())
	{
		if (nullptr != dynamic_cast<CPlayer*>(iter.second.OtherGameObject))
			return BEHAVIOR_FAIL;
	}

	return BEHAVIOR_SUCCES;
}

CIsNotRangeInPlayer * CIsNotRangeInPlayer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CIsNotRangeInPlayer* pInstance = new CIsNotRangeInPlayer(pGraphicDev);

	if (FAILED(pInstance->Ready_Behavior()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CIsNotRangeInPlayer::Clone(void)
{
	return new CIsNotRangeInPlayer(*this);
}

void CIsNotRangeInPlayer::Free()
{
	__super::Free();
}
