#pragma once
#include "ImWindow.h"

class CImInspector : public CImWindow
{
private:
	explicit CImInspector(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CImInspector();

public:
	virtual HRESULT Ready_ImWindow() override;
	virtual _int	Update(float fTimeDelta) override;

	

public:
	static CImInspector* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};

