#pragma once
#include "GameObject.h"

class CUI : public CGameObject
{
private:
	explicit CUI(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CUI();
	
	_bool		m_bShow;
};

