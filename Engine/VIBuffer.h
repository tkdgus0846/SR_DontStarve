#pragma once
#include "Component.h"

BEGIN(Engine)

enum VIBUFFER_FLAG
{
	VB_DYNAMIC,
	VB_STATIC,
};

class  CVIBuffer : public CComponent
{
protected:
	explicit CVIBuffer(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CVIBuffer(const CVIBuffer& rhs);
	virtual ~CVIBuffer();

public:
	HRESULT		Ready_Buffer(VIBUFFER_FLAG flag = VB_STATIC);
	virtual void Render_Component() override;
	
	LPDIRECT3DVERTEXBUFFER9 GetVertexBuffer() { return m_pVB; }
	LPDIRECT3DINDEXBUFFER9	GetIndexBuffer() { return m_pIB; }

protected:
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	LPDIRECT3DINDEXBUFFER9		m_pIB;

	_ulong		m_dwVtxSize;
	_ulong		m_dwVtxCnt;
	_ulong		m_dwTriCnt;
	_ulong		m_dwFVF;
	
	_ulong		m_dwIdxSize;
	D3DFORMAT	m_IdxFmt;

protected:
	virtual void Free(void);

};

END