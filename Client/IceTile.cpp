#include "IceTile.h"
#include "Export_Function.h"
#include "Player.h"

CIceTile::CIceTile(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

CIceTile::~CIceTile()
{
}

CGameObject * CIceTile::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CIceTile* pInstance = new CIceTile(pGraphicDev);
	
	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT CIceTile::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorIce", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorIce", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Collider", this, COL_ENVIRONMENT));
	pCollider->Set_BoundingBox({ 10.f, 5.f, 10.f });
	m_uMapComponent[ID_ALL].insert({ L"Collider", pCollider });
	
	return result;
}

void CIceTile::OnCollisionEnter(const Collision * collision)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(collision->OtherGameObject);

	if (pPlayer && IsBodyCollider(collision))
	{
		//if (IntersectPoint(&pPlayer->m_pTransform->m_vInfo[INFO_POS]))
		//	Set_Trigger(true);



	}
}

void CIceTile::OnCollisionStay(const Collision * collision)
{

}

void CIceTile::OnCollisionExit(const Collision * collision)
{

}

void CIceTile::InteractGameObject(const InteractInfo* tInteractInfo)
{
	m_vDir = tInteractInfo->pGameObject->m_pTransform->m_vInfo[INFO_LOOK];
	m_vDir.Normalize();
	tInteractInfo->pGameObject->m_pTransform->Move_WalkWithVec(m_vDir, 10.f, 0.016f);
}