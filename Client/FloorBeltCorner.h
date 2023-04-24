#pragma once
#include "FloorTile.h"
class CFloorBeltCorner :
	public CFloorTile
{
private:
	CFloorBeltCorner(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CFloorBeltCorner();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorBeltCorner"; }

public:
	virtual void InteractGameObject(const InteractInfo* tInteractInfo);
private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};

