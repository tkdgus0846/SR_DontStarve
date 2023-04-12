#include "stdafx.h"
#include "WallTex.h"

CWallTex::CWallTex(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVIBuffer(pGraphicDev)
{
}

CWallTex::CWallTex(const CWallTex & rhs)
	: CVIBuffer(rhs)
{
}

CWallTex::~CWallTex()
{
}

HRESULT CWallTex::Ready_Buffer()
{
	_ulong dwCntX = 6;
	_ulong dwCntY = 2;
	_ulong dwVtxItvX = VTXITV;
	_ulong dwVtxItvY = VTXITV;
	_ulong X = 5; // ���� ���� ��
	_ulong Z = 1; // ���� ���� ��

	m_dwFVF = FVF_TEX;
	m_dwVtxSize = sizeof(VTXTEX);
	m_dwVtxCnt = dwCntX * dwCntY;
	m_dwTriCnt = (dwCntX - 1) * (dwCntY - 1) * 2;

	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	FAILED_CHECK_RETURN(__super::Ready_Buffer(), E_FAIL);

	VTXTEX*		pVertex = nullptr;

	_ulong	dwIndex = 0;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);
	// ���ؽ� ���� �޸� ������ ������ ���� ����, 3�� ���ڴ� ���ؽ� ���ۿ� ����� ���ؽ��� �� ù ��° ���ؽ��� �ּҸ� ��ȯ�Ѵ�.

	for (_ulong i = 0; i < dwCntY; ++i)
	{
		for (_ulong j = 0; j < dwCntX; ++j)
		{
			dwIndex = i * dwCntX + j;

			pVertex[dwIndex].vPos = {
				_float(j * dwVtxItvX),
				_float(i * dwVtxItvY),
				 0.f};

			pVertex[dwIndex].vTexUV = {
				_float(j) / (dwCntX - 1) * (_float)X,
				1.f - _float(i) / (dwCntY - 1) * (_float)Z };
		}
	}

	m_pVB->Unlock();

	INDEX32*		pIndex = nullptr;

	_ulong	dwTriCnt = 0;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	for (_ulong i = 0; i < dwCntY - 1; ++i)
	{
		for (_ulong j = 0; j < dwCntX - 1; ++j)
		{
			dwIndex = i * dwCntX + j;

			pIndex[dwTriCnt]._0 = dwIndex + dwCntX;
			pIndex[dwTriCnt]._1 = dwIndex + dwCntX + 1;
			pIndex[dwTriCnt]._2 = dwIndex + 1;

			dwTriCnt++;

			pIndex[dwTriCnt]._0 = dwIndex + dwCntX;
			pIndex[dwTriCnt]._1 = dwIndex + 1;
			pIndex[dwTriCnt]._2 = dwIndex;

			dwTriCnt++;
		}
	}
	m_pIB->Unlock();

	return S_OK;
}

CWallTex * CWallTex::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CWallTex *	pInstance = new CWallTex(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CWallTex::Clone(void)
{
	return new CWallTex(*this);
}

void CWallTex::Free(void)
{
	__super::Free();
}
