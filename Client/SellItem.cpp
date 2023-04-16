#include "SellItem.h"
#include "WeaponItem.h"
#include "BootsItem.h"
#include "BulletItem.h"
#include "HeartItem.h"
#include "..\Engine\Export_Utility.h"
#include "Player.h"

CSellItem::CSellItem(LPDIRECT3DDEVICE9 pGraphicDev) :
	CGameObject(pGraphicDev)
{
	Set_LayerID(LAYER_NPC);
	Set_ObjTag(L"SellItem");
}

CSellItem::~CSellItem()
{
}

HRESULT CSellItem::Add_Component()
{
	CRcTex* RcTex;

	RcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(RcTex, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"RcTex", RcTex });
	m_CoinRc = RcTex;

	_int rcTexNum = m_Price;
	for (; rcTexNum != 0; rcTexNum /= 10)
	{
		RcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
		NULL_CHECK_RETURN(RcTex, E_FAIL);
		m_uMapComponent[ID_STATIC].insert({ L"RcTex", RcTex });
		m_RcVec.push_back(RcTex);
	}
	
	
	m_CoinTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Coin_Texture", this));
	NULL_CHECK_RETURN(m_CoinTexture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"Coin_Texture", m_CoinTexture });

	m_NumTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Num_Texture", this));
	m_uMapComponent[ID_STATIC].insert({ L"Num_Texture", m_NumTexture });

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Collider", this, COL_ROOMITEM));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Collider", pCollider });
	pCollider->Set_BoundingBox({ 2.5f, 2.5f, 2.5f });

	
	m_pTransform->Set_BillMode(true);

	return S_OK;
}

HRESULT CSellItem::Ready_GameObject(_vec3 vPos, SellType eID, _int iPrice, WEAPONTYPE weaponType)
{
	Set_Pos(vPos);
	Set_Price(iPrice);

	switch (eID)
	{
	case SELL_WEAPON:
	{
		m_SellItem = CWeaponItem::Create(m_pGraphicDev, vPos, weaponType);
	}
		break;
	case SELL_BOOTS:
	{
		m_SellItem = CBootsItem::Create(m_pGraphicDev, vPos);
	}
		break;
	default:
		break;
	}

	Add_GameObject(m_SellItem);
	Add_Component();
	return S_OK;
}

_int CSellItem::Update_GameObject(const _float & fTimeDelta)
{
	if (GetDead()) return OBJ_DEAD;

	__super::Update_GameObject(fTimeDelta);

	return OBJ_NOEVENT;
}

void CSellItem::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CSellItem::Render_GameObject(void)
{
	// 월드행렬을 어떻게 줄것인가?

	_vec3 coinPos = m_pTransform->m_vInfo[INFO_POS];
	coinPos.y -= 1.f;

	_matrix TransMat;
	TransMat.Translation(coinPos.x, coinPos.y, coinPos.z);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &TransMat);
	m_CoinTexture->Render_Texture();
	m_CoinRc->Render_Component();


	_vec3 numVec = coinPos;
	
	// 월드행렬 어떻게 줄것인가?
	for (int i = 0; i < m_RcVec.size(); i++)
	{
		numVec.x += 1.f;
		TransMat.Translation(numVec.x, numVec.y, numVec.z);
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &TransMat);
		m_NumTexture->Render_Texture(13);
		m_RcVec[i]->Render_Component();
	}

	__super::Render_GameObject();
}

void CSellItem::OnCollisionEnter(const Collision * collsion)
{

}

void CSellItem::OnCollisionStay(const Collision * collision)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(collision->OtherGameObject);
	if (pPlayer == nullptr) return;

	if (pPlayer && collision->MyCollider == Get_Component(L"Collider", ID_ALL))
	{
		if (pPlayer->Get_Coin() >= m_Price)
		{
			pPlayer->De_Coin(m_Price);
			m_SellItem->Set_Loot();
			SetDead();
		}
	}
}

CSellItem* CSellItem::Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 vPos, SellType eID, _int iPrice, WEAPONTYPE weaponType)
{
	CSellItem* pInstance = new CSellItem(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(vPos,eID,iPrice,weaponType)))
	{
		delete pInstance;
		pInstance = nullptr;
	}

	return pInstance;
}

void CSellItem::Free(void)
{
}
