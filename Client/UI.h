#pragma once
#include "GameObject.h"

class CUI : public CGameObject
{
protected:
	explicit CUI(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CUI();
	
	_bool		m_bShow;

public:
	_bool	CanShow() const { return m_bShow; }
	_bool   SetShow(_bool state) { m_bShow; }
};