#pragma once
#include "ImWindow.h"

class CImBaseWindow : public CImWindow
{
private:
	explicit CImBaseWindow(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CImBaseWindow();

public:
	virtual HRESULT Ready_ImWindow() override;
	virtual _int	Update(float fTimeDelta) override;

public:
	static CImBaseWindow* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};

