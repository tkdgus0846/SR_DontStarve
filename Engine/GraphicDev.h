#pragma once

#include "Base.h"
#include "Include.h"

BEGIN(Engine)

class  CGraphicDev : public CBase
{
	DECLARE_SINGLETON(CGraphicDev)

private:
	explicit CGraphicDev();
	virtual ~CGraphicDev();

public:
	LPDIRECT3DDEVICE9		Get_GraphicDev(void) { return m_pGraphicDev; }

public:
	HRESULT		Ready_GraphicDev(HWND hWnd, WINMODE eMode, const _uint& iSizeX, const _uint& iSizeY, CGraphicDev** ppGraphicDev);

	void		Render_Begin(D3DXCOLOR Color);
	void		Render_End(void);

private:
	LPDIRECT3D9			m_pSDK;
	LPDIRECT3DDEVICE9	m_pGraphicDev;

private:
	virtual void	Free(void)override;
};

END
