#include "HeartItem.h"
#include "Export_Function.h"
#include "Player.h"

CHeartItem::CHeartItem(LPDIRECT3DDEVICE9 pGraphicDev)
	:CItem(pGraphicDev)
{
	m_fY = 1.f;
	m_fMaxY = m_fY + 0.5f;
	m_fMinY = m_fY - 0.5f;
}

CHeartItem::~CHeartItem()
{
}

HRESULT CHeartItem::Add_Component()
{
	CRcTex* RcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(RcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", RcTex });

	CTexture* Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"HeartItem_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"HeartItem_Texture", Texture });

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", this, COL_ITEM));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Collider", pCollider });
	pCollider->Set_BoundingBox({ 1.0f, 1.0f, 1.0f });

	return S_OK;
}

HRESULT CHeartItem::Ready_GameObject(void)
{
	_vec3 vScale = { 0.5f, 0.5f, 0.f };
	m_pTransform->Set_Pos(30.f, 1.f, 30.f);
	m_pTransform->Set_Scale(vScale);
	__super::Ready_GameObject();
	return S_OK;
}

_int CHeartItem::Update_GameObject(const _float & fTimeDelta)
{
	ItemPatrol();
	__super::Update_GameObject(fTimeDelta);
	return 0;
}

void CHeartItem::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CHeartItem::Render_GameObject(void)
{
	__super::Render_GameObject();
}

CHeartItem * CHeartItem::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CHeartItem* pInstance = new CHeartItem(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}

	return pInstance;
}

void CHeartItem::OnCollisionEnter(const Collision * collsion)
{
	__super::OnCollisionEnter(collsion);

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(collsion->OtherGameObject);

	_int curHp = pPlayer->Get_HP();

	if (curHp < 20)
	{
		pPlayer->Gain_Hp();
	}
}

void CHeartItem::Free(void)
{
	__super::Free();
}
