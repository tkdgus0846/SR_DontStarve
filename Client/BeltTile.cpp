#include "BeltTile.h"
#include "Export_Function.h"

CBeltTile::CBeltTile(LPDIRECT3DDEVICE9 pGraphicDev)
	: CTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

CBeltTile::~CBeltTile()
{
}

CGameObject * CBeltTile::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBeltTile* pInstance = new CBeltTile(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT CBeltTile::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorBelt", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorBelt", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}

void CBeltTile::OnCollisionStay(const Collision * collision)
{
	if (IsBodyCollider(collision))
	{
		//TODO
	}
}


