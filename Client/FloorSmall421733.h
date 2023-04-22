#pragma once
#include "FloorTile.h"
class FloorSmall421733 :
	public CFloorTile
{
public:
	FloorSmall421733(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~FloorSmall421733();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorSmall421733"; }

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};
