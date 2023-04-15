#include "GrassTile.h"
#include "Export_Function.h"

CGrassTile::CGrassTile(LPDIRECT3DDEVICE9 pGraphicDev)
	: CTile(pGraphicDev)
{
	Set_ObjTag(L"GrassTile");
}

CGrassTile::~CGrassTile()
{
}

CGrassTile * CGrassTile::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CGrassTile* pInstance = new CGrassTile(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

CTile * CGrassTile::LoadSaveTarget(LPDIRECT3DDEVICE9 pGraphicDev)
{
	return Create(pGraphicDev);
}

HRESULT CGrassTile::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorGrass #421873", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorGrass #421873", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}

void CGrassTile::OnCollisionStay(const Collision * collision)
{
	if (IsBodyCollider(collision))
	{
		//TODO
	}
}