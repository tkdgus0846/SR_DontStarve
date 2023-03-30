#include "stdafx.h"
#include "CubeTex.h"


CCubeTex::CCubeTex(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVIBuffer(pGraphicDev)
{
}

CCubeTex::CCubeTex(const CCubeTex & rhs)
	: CVIBuffer(rhs)
{
}

CCubeTex::~CCubeTex()
{
}

HRESULT CCubeTex::Ready_Buffer(void)
{

	m_dwFVF = FVF_CUBE;
	m_dwVtxSize = sizeof(VTXCUBE);
	m_dwVtxCnt = 8;
	m_dwTriCnt = 12;

	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	FAILED_CHECK_RETURN(__super::Ready_Buffer(), E_FAIL);

	VTXCUBE*		pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);
	// ���ؽ� ���� �޸� ������ ������ ���� ����, 3�� ���ڴ� ���ؽ� ���ۿ� ����� ���ؽ��� �� ù ��° ���ؽ��� �ּҸ� ��ȯ�Ѵ�.

	pVertex[0].vPos = { -1.f, 1.f, -1.f };
	pVertex[0].vTexUV = pVertex[0].vPos;

	pVertex[1].vPos = { 1.f, 1.f, -1.f };
	pVertex[1].vTexUV = pVertex[1].vPos;

	pVertex[2].vPos = { 1.f, -1.f, -1.f };
	pVertex[2].vTexUV = pVertex[2].vPos;

	pVertex[3].vPos = { -1.f, -1.f, -1.f };
	pVertex[3].vTexUV = pVertex[3].vPos;


	pVertex[4].vPos = { -1.f, 1.f, 1.f };
	pVertex[4].vTexUV = pVertex[4].vPos;

	pVertex[5].vPos = { 1.f, 1.f, 1.f };
	pVertex[5].vTexUV = pVertex[5].vPos;

	pVertex[6].vPos = { 1.f, -1.f, 1.f };
	pVertex[6].vTexUV = pVertex[6].vPos;

	pVertex[7].vPos = { -1.f, -1.f, 1.f };
	pVertex[7].vTexUV = pVertex[7].vPos;


	m_pVB->Unlock();

	INDEX32*		pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	// x+
	pIndex[0]._0 = 1;
	pIndex[0]._1 = 5;
	pIndex[0]._2 = 6;

	pIndex[1]._0 = 1;
	pIndex[1]._1 = 6;
	pIndex[1]._2 = 2;

	// x-
	pIndex[2]._0 = 4;
	pIndex[2]._1 = 0;
	pIndex[2]._2 = 3;

	pIndex[3]._0 = 4;
	pIndex[3]._1 = 3;
	pIndex[3]._2 = 7;


	// y+
	pIndex[4]._0 = 4;
	pIndex[4]._1 = 5;
	pIndex[4]._2 = 1;

	pIndex[5]._0 = 4;
	pIndex[5]._1 = 1;
	pIndex[5]._2 = 0;

	// y-
	pIndex[6]._0 = 3;
	pIndex[6]._1 = 2;
	pIndex[6]._2 = 6;

	pIndex[7]._0 = 3;
	pIndex[7]._1 = 6;
	pIndex[7]._2 = 7;

	// z+
	pIndex[8]._0 = 7;
	pIndex[8]._1 = 6;
	pIndex[8]._2 = 5;

	pIndex[9]._0 = 7;
	pIndex[9]._1 = 5;
	pIndex[9]._2 = 4;

	// z-
	pIndex[10]._0 = 0;
	pIndex[10]._1 = 1;
	pIndex[10]._2 = 2;

	pIndex[11]._0 = 0;
	pIndex[11]._1 = 2;
	pIndex[11]._2 = 3;

	m_pIB->Unlock();

	return S_OK;
}

void CCubeTex::Render_Buffer(void)
{
	__super::Render_Buffer();
}

CCubeTex * CCubeTex::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCubeTex *	pInstance = new CCubeTex(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}
CComponent * CCubeTex::Clone(void)
{
	return new CCubeTex(*this);
}

void CCubeTex::Free(void)
{
	__super::Free();
}
