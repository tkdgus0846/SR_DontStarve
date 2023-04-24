#pragma once
#include "FloorTile.h"


class FloorVent
	: public CFloorTile
{
public:
	FloorVent(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~FloorVent();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorVent"; }

private:
	virtual HRESULT Add_Component() override;
};

