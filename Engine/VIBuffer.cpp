#include "stdafx.h"
#include "VIBuffer.h"
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"


CVIBuffer::CVIBuffer(LPDIRECT3DDEVICE9 pGraphicDev)
	: CComponent(pGraphicDev)
	, m_pVB(nullptr)
	, m_pIB(nullptr)
	, m_dwFVF(0)
	, m_dwVtxSize(0)
	, m_dwVtxCnt(0)
	, m_dwTriCnt(0)
	, m_dwIdxSize(0)
{
}

CVIBuffer::CVIBuffer(const CVIBuffer & rhs)
	:CComponent(rhs)
	, m_pVB(rhs.m_pVB)
	, m_pIB(rhs.m_pIB)
	, m_dwFVF(rhs.m_dwFVF)
	, m_dwVtxSize(rhs.m_dwVtxSize)
	, m_dwVtxCnt(rhs.m_dwVtxCnt)
	, m_dwTriCnt(rhs.m_dwTriCnt)
	, m_dwIdxSize(rhs.m_dwIdxSize)
	, m_IdxFmt(rhs.m_IdxFmt)
{
	//m_pVB->AddRef();
	//m_pIB->AddRef();
	//m_RenderOrder = 3;
	//m_bRenderFlag = FALSE;

	// Create a new vertex buffer
	if (FAILED(m_pGraphicDev->CreateVertexBuffer(m_dwVtxCnt * m_dwVtxSize,
		D3DUSAGE_DYNAMIC,
		m_dwFVF,
		D3DPOOL_DEFAULT,
		&m_pVB,
		0)))
	{
		MSG_BOX("CreateVertexBuffer Failed");
		return;
	}

	// Copy the content of the original vertex buffer to the new one
	void *pSrcData = nullptr, *pDstData = nullptr;
	if (SUCCEEDED(rhs.m_pVB->Lock(0, 0, &pSrcData, D3DLOCK_READONLY)) &&
		SUCCEEDED(m_pVB->Lock(0, 0, &pDstData, 0)))
	{
		memcpy(pDstData, pSrcData, m_dwVtxCnt * m_dwVtxSize);
		m_pVB->Unlock();
		rhs.m_pVB->Unlock();
	}

	// Create a new index buffer
	if (FAILED(m_pGraphicDev->CreateIndexBuffer(m_dwIdxSize * m_dwTriCnt,
		0,
		m_IdxFmt,
		D3DPOOL_MANAGED,
		&m_pIB,
		nullptr)))
	{
		MSG_BOX("CreateIndexBuffer Failed");
		return;
	}

	// Copy the content of the original index buffer to the new one
	if (SUCCEEDED(rhs.m_pIB->Lock(0, 0, &pSrcData, D3DLOCK_READONLY)) &&
		SUCCEEDED(m_pIB->Lock(0, 0, &pDstData, 0)))
	{
		memcpy(pDstData, pSrcData, m_dwIdxSize * m_dwTriCnt);
		m_pIB->Unlock();
		rhs.m_pIB->Unlock();
	}

	m_RenderOrder = 3;
	m_bRenderFlag = FALSE;
}

CVIBuffer::~CVIBuffer()
{
}

HRESULT CVIBuffer::Ready_Buffer(VIBUFFER_FLAG flag)
{
	
	if (flag == VB_STATIC)
	{
		if (FAILED(m_pGraphicDev->CreateVertexBuffer(m_dwVtxCnt * m_dwVtxSize,  // ���� ������ ũ��
			0,						// ���۸� ����� ���(0�� ��� ���� ����,  D3DUSAGE_DYNAMIC ���� ����)
			m_dwFVF,				// ������ �ɼ�			
			D3DPOOL_MANAGED,
			&m_pVB,					// ������ ���ؽ� ���۸� ������ �޸� �ּ�
			nullptr)))
		{
			MSG_BOX("CreateVertexBuffer Failed");
			return E_FAIL;
		}
	}
	else
	{
		FAILED_CHECK_RETURN_MSG
		(
			m_pGraphicDev->CreateVertexBuffer(
			m_dwVtxCnt * m_dwVtxSize,
			D3DUSAGE_DYNAMIC,
			m_dwFVF,
			D3DPOOL_DEFAULT,
			&m_pVB,
			0),
			E_FAIL,
			L"���� ���ؽ� ���� ���� ����"
		);
	}
	

	if (FAILED(m_pGraphicDev->CreateIndexBuffer(m_dwIdxSize * m_dwTriCnt,
												0,
												m_IdxFmt,
												D3DPOOL_MANAGED,
												&m_pIB,
												nullptr)))
	{
		MSG_BOX("CreateIndexBuffer Failed");
		return E_FAIL;
	}

	return S_OK;
}

void CVIBuffer::Render_Component()
{
	// SetStreamSource: �׸��� ��ġ�� ���� �׸����� �ϴ� ���ؽ� ������ �����ϴ� �Լ�
	// 1. �� ��° ���Կ� ������ ���ΰ�
	// 2. � ������ ������ ���ΰ�
	// 3. ��𼭺��� �׸��� ������ ������ ���ΰ�
	// 4. � ������ �׸��� ������ ������ ���ΰ�

	if (m_bRenderFlag == false)
	{
		const _matrix* mat = m_pGameObject->m_pTransform->Get_WorldMatrixPointer();
		m_pGraphicDev->SetTransform(D3DTS_WORLD, mat);
	}
	

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pGraphicDev->SetStreamSource(0, m_pVB, 0, m_dwVtxSize);

	m_pGraphicDev->SetFVF(m_dwFVF);

	m_pGraphicDev->SetIndices(m_pIB);

	m_pGraphicDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_dwVtxCnt, 0, m_dwTriCnt);

	//m_pGraphicDev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_dwTriCnt);
	// �׸��� �Լ�
	/*1. �ﰢ���� �׸��� ���
	2. �� ��° ���ؽ����� �׸� ���ΰ�
	3. �׸� �ﰢ���� ����*/
}


void Engine::CVIBuffer::Free(void)
{
	Safe_Release(m_pIB);
	Safe_Release(m_pVB);

	__super::Free();
}
