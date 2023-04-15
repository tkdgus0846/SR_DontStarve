#include "BloodTile.h"
#include "Export_Function.h"

CBloodTile::CBloodTile(LPDIRECT3DDEVICE9 pGraphicDev)
	: CTile(pGraphicDev)
{
	Set_ObjTag(L"BloodTile");
}

CBloodTile::~CBloodTile()
{
}

CBloodTile * CBloodTile::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBloodTile* pInstance = new CBloodTile(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

CTile * CBloodTile::LoadSaveTarget(LPDIRECT3DDEVICE9 pGraphicDev)
{
	return Create(pGraphicDev);
}

HRESULT CBloodTile::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorBlood", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorBlood", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}

void CBloodTile::OnCollisionStay(const Collision * collision)
{
	if (IsBodyCollider(collision))
	{
		//TODO
	}
}