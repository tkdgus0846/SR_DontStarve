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
	HRESULT result = __super::Ready_GameObject();

	return result;
}

_int CTile::Update_GameObject(const _float & fTimeDelta)
{
	__super::Update_GameObject(fTimeDelta);
	return _int();
}

void CTile::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CTile::Render_GameObject(void)
{
	__super::Render_GameObject();
}

void CTile::Free(void)
{
	__super::Free();
}

