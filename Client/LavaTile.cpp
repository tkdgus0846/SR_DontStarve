#include "LavaTile.h"
#include "Export_Function.h"

CLavaTile::CLavaTile(LPDIRECT3DDEVICE9 pGraphicDev)
	: CTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

CLavaTile::~CLavaTile()
{
}

CGameObject * CLavaTile::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLavaTile* pInstance = new CLavaTile(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

CGameObject * CLavaTile::LoadSaveTarget(LPDIRECT3DDEVICE9 pGraphicDev)
{
	return Create(pGraphicDev);
}

HRESULT CLavaTile::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorLava", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorLava", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);
	m_pAnimation->SelectState(ANIM_IDLE);

	return result;
}

void CLavaTile::OnCollisionStay(const Collision * collision)
{
	if (IsBodyCollider(collision))
	{
		//TODO
	}
}