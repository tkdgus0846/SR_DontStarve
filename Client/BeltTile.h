#pragma once
#include "Tile.h"
class CBeltTile :
	public CTile
{
public:
	CBeltTile(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CBeltTile();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"BeltTile"; }

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};
