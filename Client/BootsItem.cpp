#include "BootsItem.h"
#include "Export_Function.h"
#include "Player.h"


CBootsItem::CBootsItem(LPDIRECT3DDEVICE9 pGraphicDev)
	: CItem(pGraphicDev)
{
	Set_ObjTag(L"BootsItem");
	m_bDrop = true;
	m_bBill = false;
}

CBootsItem::~CBootsItem()
{
}

HRESULT CBootsItem::Add_Component()
{
	CRcTex* RcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(RcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", RcTex });

	CTexture* Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"BootsItem_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"BootsItem_Texture", Texture });

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Collider", this, COL_ITEM));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Collider", pCollider });
	pCollider->Set_BoundingBox({ 1.0f, 1.0f, 1.0f });

	pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Range", this, COL_ITEM));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Range", pCollider });
	pCollider->Set_BoundingBox({ 10.f, 3.0f, 10.f });

	return S_OK;
}

HRESULT CBootsItem::Ready_GameObject(_vec3 vPos)
{
	_vec3 vScale{ 1.f, 1.f, 0.f };
	m_pTransform->Set_Pos(vPos);
	m_pTransform->Set_Scale(vScale);
	__super::Ready_GameObject();

	return S_OK;
}

_int CBootsItem::Update_GameObject(const _float & fTimeDelta)
{
	WeaponRotationZ();
	m_fAngle += 10.f;

	__super::Update_GameObject(fTimeDelta);
	
	if (GetDead()) return OBJ_DEAD;

	return OBJ_NOEVENT;
}

void CBootsItem::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CBootsItem::Render_GameObject(void)
{
	__super::Render_GameObject();
}

CBootsItem * CBootsItem::Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 vPos)
{
	CBootsItem* pInstance = new CBootsItem(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(vPos)))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

void CBootsItem::OnCollisionEnter(const Collision * collsion)
{
	__super::OnCollisionEnter(collsion);

	
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(collsion->OtherGameObject);

	if (pPlayer && collsion->MyCollider == Get_Component(L"Collider", ID_ALL))
	{
		pPlayer->Plus_Speed(7);
	}

}

void CBootsItem::OnCollisionStay(const Collision * collision)
{

	__super::OnCollisionStay(collision);
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(collision->OtherGameObject);

	ItemMagnetic(pPlayer);
}

void CBootsItem::WeaponRotationZ()
{
	_matrix matRot;
	_vec3	vecRot{ 1.f, 0.f, 1.f };
	D3DXMatrixRotationY(&matRot, D3DXToRadian(m_fAngle));
	D3DXVec3TransformCoord(&vecRot, &vecRot, &matRot);
	m_pTransform->m_vInfo[INFO_LOOK] = vecRot;
	m_pTransform->m_vInfo[INFO_RIGHT] = vecRot;
}

void CBootsItem::Free(void)
{
	__super::Free();
}
