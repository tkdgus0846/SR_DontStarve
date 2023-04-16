#pragma once
#include "Tile.h"
class CLavaTile :
	public CTile
{
private:
	CLavaTile(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CLavaTile();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"LavaTile"; }
	CGameObject* LoadSaveTarget(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};

