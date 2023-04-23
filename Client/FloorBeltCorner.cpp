#include "FloorBeltCorner.h"
#include "Export_Function.h"



CFloorBeltCorner::CFloorBeltCorner(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}


CFloorBeltCorner::~CFloorBeltCorner()
{
}

CGameObject * CFloorBeltCorner::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CFloorBeltCorner* pInstance = new CFloorBeltCorner(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}


HRESULT CFloorBeltCorner::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorBeltCorner", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorBeltCorner", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}

void CFloorBeltCorner::OnCollisionStay(const Collision * collision)
{
	if (IsBodyCollider(collision))
	{
		//TODO
	}
}