#include "ElectricTile.h"
#include "Export_Function.h"


CElectricTile::CElectricTile(LPDIRECT3DDEVICE9 pGraphicDev)
	: CTile(pGraphicDev)
{
	Set_ObjTag(L"ElectricTile");
}

CElectricTile::~CElectricTile()
{
}

CElectricTile * CElectricTile::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CElectricTile* pInstance = new CElectricTile(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

CTile * CElectricTile::LoadSaveTarget(LPDIRECT3DDEVICE9 pGraphicDev)
{
	return Create(pGraphicDev);
}

HRESULT CElectricTile::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorElectric", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorElectric", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}

void CElectricTile::OnCollisionStay(const Collision * collision)
{
	if (IsBodyCollider(collision))
	{
		//TODO
	}
}