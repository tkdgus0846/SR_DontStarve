#pragma once
#include "GameObject.h"

class CItem :
	public CGameObject
{
private:
	CItem(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CItem();

public:
	virtual _int Update_GameObject(const _float& fTimeDelta) override;

};