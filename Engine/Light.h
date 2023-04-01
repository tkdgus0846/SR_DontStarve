#pragma once

#include "Base.h"

BEGIN(Engine)

class CLight : public  CBase
{
private:
	explicit CLight(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CLight();

public:
	HRESULT					Ready_Light(const D3DLIGHT9* pLightInfo, const _uint& iIndex);

private:
	LPDIRECT3DDEVICE9		m_pGraphicDev;
	D3DLIGHT9				m_tLightInfo;
	_uint					m_iIndex;

public:
	static CLight*		Create(LPDIRECT3DDEVICE9 pGraphicDev, 
								const D3DLIGHT9* pLightInfo,
								const _uint& iIndex);

private:
	virtual void		Free(void);
};

END
