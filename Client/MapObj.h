#pragma once

#include "Include.h"
#include "GameObject.h"

class CMapObj :
	public CGameObject
{
protected:
	explicit CMapObj(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CMapObj();
	virtual void Render_GameObject(void) override;
};