#include "stdafx.h"
#include "RcCol.h"


CRcCol::CRcCol(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVIBuffer(pGraphicDev)
{
}

CRcCol::CRcCol(const CRcCol & rhs)
	:CVIBuffer(rhs)
{
}

CRcCol::~CRcCol()
{
}

HRESULT CRcCol::Ready_Buffer(void)
{
#pragma region ����

	/*m_dwFVF = FVF_COL;
	m_dwVtxSize = sizeof(VTXCOL);
	m_dwVtxCnt = 6;
	m_dwTriCnt = 2;

	FAILED_CHECK_RETURN(__super::Ready_Buffer(), E_FAIL);

	VTXCOL*		pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);
	// ���ؽ� ���� �޸� ������ ������ ���� ����, 3�� ���ڴ� ���ؽ� ���ۿ� ����� ���ؽ��� �� ù ��° ���ؽ��� �ּҸ� ��ȯ�Ѵ�.

	pVertex[0].vPos = { -1.f, 1.f, 0.f };
	pVertex[0].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	pVertex[1].vPos = { 1.f, 1.f, 0.f };
	pVertex[1].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	pVertex[2].vPos = { 1.f, -1.f, 0.f };
	pVertex[2].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	// ���� �Ʒ�

	pVertex[3].vPos = { -1.f, 1.f, 0.f };
	pVertex[3].dwColor = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);

	pVertex[4].vPos = { 1.f, -1.f, 0.f };
	pVertex[4].dwColor = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);

	pVertex[5].vPos = { -1.f, -1.f, 0.f };
	pVertex[5].dwColor = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);

	m_pVB->Unlock();*/

#pragma endregion ����
	
	m_dwFVF = FVF_COL;
	m_dwVtxSize = sizeof(VTXCOL);
	m_dwVtxCnt = 4;
	m_dwTriCnt = 2;

	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	FAILED_CHECK_RETURN(__super::Ready_Buffer(), E_FAIL);

	VTXCOL*		pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);
	// ���ؽ� ���� �޸� ������ ������ ���� ����, 3�� ���ڴ� ���ؽ� ���ۿ� ����� ���ؽ��� �� ù ��° ���ؽ��� �ּҸ� ��ȯ�Ѵ�.
	
	pVertex[0].vPos = { -1.f, 1.f, 0.f };
	pVertex[0].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	pVertex[1].vPos = { 1.f, 1.f, 0.f };
	pVertex[1].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	pVertex[2].vPos = { 1.f, -1.f, 0.f };
	pVertex[2].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	pVertex[3].vPos = { -1.f, -1.f, 0.f };
	pVertex[3].dwColor = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);

	m_pVB->Unlock();

	INDEX32*		pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	pIndex[0]._0 = 0;
	pIndex[0]._1 = 1;
	pIndex[0]._2 = 2;

	pIndex[1]._0 = 0;
	pIndex[1]._1 = 2;
	pIndex[1]._2 = 3;

	m_pIB->Unlock();

	return S_OK;
}

void CRcCol::Render_Buffer(void)
{
	__super::Render_Buffer();
}

CRcCol * CRcCol::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRcCol *	pInstance = new CRcCol(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}
CComponent * CRcCol::Clone(void)
{
	return new CRcCol(*this);
}

void CRcCol::Free(void)
{
	__super::Free();
}
