#include "RangeCheck.h"

#include "Player.h"
#include "Export_Function.h"

CRangeCheck::CRangeCheck(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBehavior(pGraphicDev)
{
}

CRangeCheck::CRangeCheck(const CRangeCheck & rhs)
	: CBehavior(rhs)
{
}

CRangeCheck::~CRangeCheck()
{
}

HRESULT CRangeCheck::Ready_Behavior()
{
	return S_OK;
}

_int CRangeCheck::Update_Component(const _float & fTimeDelta)
{
	CComponent* pComponent = m_pGameObject->Get_Component(L"Range", ID_ALL);

	if (dynamic_cast<CCollider*>(pComponent)->Get_ColliderList().empty())
		return BEHAVIOR_FAIL;
	else
	{
		for (auto iter : dynamic_cast<CCollider*>(pComponent)->Get_ColliderList())
		{
			if (nullptr != dynamic_cast<CPlayer*>(iter.second.OtherGameObject))
				return BEHAVIOR_SUCCES;
		}
	}

	return BEHAVIOR_FAIL;
}

void CRangeCheck::LateUpdate_Component(void)
{
}

void CRangeCheck::Render_Component(void)
{
}

CRangeCheck * CRangeCheck::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRangeCheck* pInstance = new CRangeCheck(pGraphicDev);

	if (FAILED(pInstance->Ready_Behavior()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CRangeCheck::Clone(void)
{
	return new CRangeCheck(*this);
}

void CRangeCheck::Free()
{
	__super::Free();
}
