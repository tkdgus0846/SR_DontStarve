#pragma once
#include "FloorTile.h"
class CIceTile :
	public CFloorTile
{
private:
	CIceTile(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CIceTile();

public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"IceTile"; }
	CGameObject* LoadSaveTarget(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};