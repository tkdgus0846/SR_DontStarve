#include "stdafx.h"
#include "Tile.h"

#include "Export_Function.h"

CTile::CTile(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
}


CTile::~CTile()
{
}

HRESULT CTile::Ready_GameObject(void)
{
	return E_NOTIMPL;
}

_int CTile::Update_GameObject(const _float & fTimeDelta)
{
	return _int();
}

void CTile::LateUpdate_GameObject(void)
{
}

void CTile::Render_GameObject(void)
{
}

void CTile::Free(void)
{
}

