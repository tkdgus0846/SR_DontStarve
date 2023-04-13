#include "stdafx.h"
#include "FrustrumNormalTex.h"


CFrustrumNormalTex::CFrustrumNormalTex(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVIBuffer(pGraphicDev)
{
}

CFrustrumNormalTex::CFrustrumNormalTex(const CFrustrumNormalTex & rhs)
	: CVIBuffer(rhs)
{
}

CFrustrumNormalTex::~CFrustrumNormalTex()
{
}

HRESULT CFrustrumNormalTex::Ready_Buffer(void)
{
	m_dwFVF = FVF_CUBE;
	m_dwVtxSize = sizeof(VTXCUBE);
	m_dwVtxCnt = 8;
	m_dwTriCnt = 12;

	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	FAILED_CHECK_RETURN(__super::Ready_Buffer(), E_FAIL);

	VTXCUBE*		pVertex = nullptr;
	INDEX32*		pIndex = nullptr;
	_vec3		vDest, vSrc, vNormal;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);
	m_pIB->Lock(0, 0, (void**)&pIndex, 0);
	// 버텍스 버퍼 메모리 공간의 접근을 막는 행위, 3번 인자는 버텍스 버퍼에 저장된 버텍스들 중 첫 번째 버텍스의 주소를 반환한다.

	pVertex[0].vPos = { -1.0f, 0.0f,  1.0f };
	//pVertex[0].vNormal = { 0.f, 0.f, 0.f };
	pVertex[0].vTexUV = pVertex[0].vPos;

	pVertex[1].vPos = { 1.0f, 0.0f,  1.0f };
	//pVertex[1].vNormal = { 0.f, 0.f, 0.f };
	pVertex[1].vTexUV = pVertex[1].vPos;

	pVertex[2].vPos = { 1.0f, 0.0f, -1.0f };
	//pVertex[2].vNormal = { 0.f, 0.f, 0.f };
	pVertex[2].vTexUV = pVertex[2].vPos;

	pVertex[3].vPos = { -1.0f, 0.0f, -1.0f };
	//pVertex[3].vNormal = { 0.f, 0.f, 0.f };
	pVertex[3].vTexUV = pVertex[3].vPos;


	_float fx = 0.2f;

	pVertex[4].vPos = { -fx, 1.0f,  fx };
	//pVertex[4].vNormal = { 0.f, 0.f, 0.f };
	pVertex[4].vTexUV = pVertex[4].vPos;

	pVertex[5].vPos = { fx, 1.0f,  fx };
	//pVertex[5].vNormal = { 0.f, 0.f, 0.f };
	pVertex[5].vTexUV = pVertex[5].vPos;

	pVertex[6].vPos = { fx, 1.0f, -fx };
	//pVertex[6].vNormal = { 0.f, 0.f, 0.f };
	pVertex[6].vTexUV = pVertex[6].vPos;

	pVertex[7].vPos = { -fx, 1.0f, -fx };
	//pVertex[7].vNormal = { 0.f, 0.f, 0.f };
	pVertex[7].vTexUV = pVertex[7].vPos;


	// 인덱스 버퍼

	// x+
	pIndex[0]._0 = 1;
	pIndex[0]._1 = 5;
	pIndex[0]._2 = 6;

	//vDest = pVertex[pIndex[0]._1].vPos - pVertex[pIndex[0]._0].vPos;
	//vSrc = pVertex[pIndex[0]._2].vPos - pVertex[pIndex[0]._1].vPos;
	//D3DXVec3Cross(&vNormal, &vDest, &vSrc);
	//pVertex[pIndex[0]._0].vNormal += vNormal;
	//pVertex[pIndex[0]._1].vNormal += vNormal;
	//pVertex[pIndex[0]._2].vNormal += vNormal;

	pIndex[1]._0 = 1;
	pIndex[1]._1 = 6;
	pIndex[1]._2 = 2;

	//vDest = pVertex[pIndex[1]._1].vPos - pVertex[pIndex[1]._0].vPos;
	//vSrc = pVertex[pIndex[1]._2].vPos - pVertex[pIndex[1]._1].vPos;
	//D3DXVec3Cross(&vNormal, &vDest, &vSrc);
	//pVertex[pIndex[1]._0].vNormal += vNormal;
	//pVertex[pIndex[1]._1].vNormal += vNormal;
	//pVertex[pIndex[1]._2].vNormal += vNormal;

	// x-
	pIndex[2]._0 = 4;
	pIndex[2]._1 = 0;
	pIndex[2]._2 = 3;

	//vDest = pVertex[pIndex[2]._1].vPos - pVertex[pIndex[2]._0].vPos;
	//vSrc = pVertex[pIndex[2]._2].vPos - pVertex[pIndex[2]._1].vPos;
	//D3DXVec3Cross(&vNormal, &vDest, &vSrc);
	//pVertex[pIndex[2]._0].vNormal += vNormal;
	//pVertex[pIndex[2]._1].vNormal += vNormal;
	//pVertex[pIndex[2]._2].vNormal += vNormal;

	pIndex[3]._0 = 4;
	pIndex[3]._1 = 3;
	pIndex[3]._2 = 7;

	//vDest = pVertex[pIndex[3]._1].vPos - pVertex[pIndex[3]._0].vPos;
	//vSrc = pVertex[pIndex[3]._2].vPos - pVertex[pIndex[3]._1].vPos;
	//D3DXVec3Cross(&vNormal, &vDest, &vSrc);
	//pVertex[pIndex[3]._0].vNormal += vNormal;
	//pVertex[pIndex[3]._1].vNormal += vNormal;
	//pVertex[pIndex[3]._2].vNormal += vNormal;

	// y+
	pIndex[4]._0 = 4;
	pIndex[4]._1 = 5;
	pIndex[4]._2 = 1;

	//vDest = pVertex[pIndex[4]._1].vPos - pVertex[pIndex[4]._0].vPos;
	//vSrc = pVertex[pIndex[4]._2].vPos - pVertex[pIndex[4]._1].vPos;
	//D3DXVec3Cross(&vNormal, &vDest, &vSrc);
	//pVertex[pIndex[4]._0].vNormal += vNormal;
	//pVertex[pIndex[4]._1].vNormal += vNormal;
	//pVertex[pIndex[4]._2].vNormal += vNormal;

	pIndex[5]._0 = 4;
	pIndex[5]._1 = 1;
	pIndex[5]._2 = 0;

	//vDest = pVertex[pIndex[5]._1].vPos - pVertex[pIndex[5]._0].vPos;
	//vSrc = pVertex[pIndex[5]._2].vPos - pVertex[pIndex[5]._1].vPos;
	//D3DXVec3Cross(&vNormal, &vDest, &vSrc);
	//pVertex[pIndex[5]._0].vNormal += vNormal;
	//pVertex[pIndex[5]._1].vNormal += vNormal;
	//pVertex[pIndex[5]._2].vNormal += vNormal;

	// y-
	pIndex[6]._0 = 3;
	pIndex[6]._1 = 2;
	pIndex[6]._2 = 6;

	//vDest = pVertex[pIndex[6]._1].vPos - pVertex[pIndex[6]._0].vPos;
	//vSrc = pVertex[pIndex[6]._2].vPos - pVertex[pIndex[6]._1].vPos;
	//D3DXVec3Cross(&vNormal, &vDest, &vSrc);
	//pVertex[pIndex[6]._0].vNormal += vNormal;
	//pVertex[pIndex[6]._1].vNormal += vNormal;
	//pVertex[pIndex[6]._2].vNormal += vNormal;

	pIndex[7]._0 = 3;
	pIndex[7]._1 = 6;
	pIndex[7]._2 = 7;

	//vDest = pVertex[pIndex[7]._1].vPos - pVertex[pIndex[7]._0].vPos;
	//vSrc = pVertex[pIndex[7]._2].vPos - pVertex[pIndex[7]._1].vPos;
	//D3DXVec3Cross(&vNormal, &vDest, &vSrc);
	//pVertex[pIndex[7]._0].vNormal += vNormal;
	//pVertex[pIndex[7]._1].vNormal += vNormal;
	//pVertex[pIndex[7]._2].vNormal += vNormal;

	// z+
	pIndex[8]._0 = 7;
	pIndex[8]._1 = 6;
	pIndex[8]._2 = 5;

	//vDest = pVertex[pIndex[8]._1].vPos - pVertex[pIndex[8]._0].vPos;
	//vSrc = pVertex[pIndex[8]._2].vPos - pVertex[pIndex[8]._1].vPos;
	//D3DXVec3Cross(&vNormal, &vDest, &vSrc);
	//pVertex[pIndex[8]._0].vNormal += vNormal;
	//pVertex[pIndex[8]._1].vNormal += vNormal;
	//pVertex[pIndex[8]._2].vNormal += vNormal;

	pIndex[9]._0 = 7;
	pIndex[9]._1 = 5;
	pIndex[9]._2 = 4;

	//vDest = pVertex[pIndex[9]._1].vPos - pVertex[pIndex[9]._0].vPos;
	//vSrc = pVertex[pIndex[9]._2].vPos - pVertex[pIndex[9]._1].vPos;
	//D3DXVec3Cross(&vNormal, &vDest, &vSrc);
	//pVertex[pIndex[9]._0].vNormal += vNormal;
	//pVertex[pIndex[9]._1].vNormal += vNormal;
	//pVertex[pIndex[9]._2].vNormal += vNormal;

	// z-
	pIndex[10]._0 = 0;
	pIndex[10]._1 = 1;
	pIndex[10]._2 = 2;

	//vDest = pVertex[pIndex[10]._1].vPos - pVertex[pIndex[10]._0].vPos;
	//vSrc = pVertex[pIndex[10]._2].vPos - pVertex[pIndex[10]._1].vPos;
	//D3DXVec3Cross(&vNormal, &vDest, &vSrc);
	//pVertex[pIndex[10]._0].vNormal += vNormal;
	//pVertex[pIndex[10]._1].vNormal += vNormal;
	//pVertex[pIndex[10]._2].vNormal += vNormal;

	pIndex[11]._0 = 0;
	pIndex[11]._1 = 2;
	pIndex[11]._2 = 3;

	//vDest = pVertex[pIndex[11]._1].vPos - pVertex[pIndex[11]._0].vPos;
	//vSrc = pVertex[pIndex[11]._2].vPos - pVertex[pIndex[11]._1].vPos;
	//D3DXVec3Cross(&vNormal, &vDest, &vSrc);
	//pVertex[pIndex[11]._0].vNormal += vNormal;
	//pVertex[pIndex[11]._1].vNormal += vNormal;
	//pVertex[pIndex[11]._2].vNormal += vNormal;

	//for (_ulong i = 0; i < m_dwVtxCnt; ++i)
	//	D3DXVec3Normalize(&pVertex[i].vNormal, &pVertex[i].vNormal);

	m_pIB->Unlock();
	m_pVB->Unlock();

	return S_OK;
}

CFrustrumNormalTex * CFrustrumNormalTex::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CFrustrumNormalTex *	pInstance = new CFrustrumNormalTex(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}
CComponent * CFrustrumNormalTex::Clone(void)
{
	return new CFrustrumNormalTex(*this);
}

void CFrustrumNormalTex::Free(void)
{
	__super::Free();
}

void CFrustrumNormalTex::ComputeNormal(_vec3 * p0, _vec3 * p1, _vec3 * p2, _vec3 * out)
{
	D3DXVECTOR3 u = *p1 - *p0;
	D3DXVECTOR3 v = *p2 - *p0;

	D3DXVec3Cross(out, &u, &v);
	D3DXVec3Normalize(out, out);
}