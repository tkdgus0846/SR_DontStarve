#pragma once
#include "VIBuffer.h"

BEGIN(Engine)

class  CRcTex : public CVIBuffer
{
private:
	explicit CRcTex(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CRcTex(const CRcTex& rhs);
	virtual ~CRcTex();

public:
	HRESULT		Ready_Buffer(VIBUFFER_FLAG bufferFlag = VB_STATIC);
	void		Edit_VB(_float fX);
	void		Edit_UV(_float fX);

public:
	static CRcTex*		Create(LPDIRECT3DDEVICE9 pGraphicDev, VIBUFFER_FLAG bufferFlag = VB_STATIC);
	virtual CComponent*	Clone(void);
private:
	virtual void Free(void);

};

END