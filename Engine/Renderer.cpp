#include "stdafx.h"
#include "Renderer.h"
#include "Export_Function.h"

IMPLEMENT_SINGLETON(CRenderer)

CRenderer::CRenderer()
{
}

CRenderer::~CRenderer()
{
	Free();
}

void CRenderer::Add_RenderGroup(RENDERID eID, CGameObject * pGameObject)
{
	if (RENDER_END <= eID || nullptr == pGameObject)
		return;

	m_RenderGroup[eID].push_back(pGameObject);
	pGameObject->AddRef();
}

void CRenderer::Render_GameObject(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	
	Render_Priority(pGraphicDev);
	Render_NonAlpha(pGraphicDev);
	Render_Alpha(pGraphicDev);
	Render_UI(pGraphicDev);

	Clear_RenderGroup();
}

void CRenderer::Clear_RenderGroup(void)
{
	for (size_t i = 0; i < RENDER_END; ++i)
	{
		for_each(m_RenderGroup[i].begin(), m_RenderGroup[i].end(), CDeleteObj());
		m_RenderGroup[i].clear();
	}
}

void CRenderer::Render_Priority(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	for (auto& iter : m_RenderGroup[RENDER_PRIORITY])
		iter->Render_GameObject();

}

void CRenderer::Render_NonAlpha(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	for (auto& iter : m_RenderGroup[RENDER_NONALPHA])
		iter->Render_GameObject();
}

void CRenderer::Render_Alpha(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	m_RenderGroup[RENDER_ALPHA].sort([](CGameObject* pDst, CGameObject* pSrc)->bool { return pDst->Get_ViewZ() > pSrc->Get_ViewZ();	});

	for (auto& iter : m_RenderGroup[RENDER_ALPHA])
		iter->Render_GameObject();

	pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

void CRenderer::Render_UI(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	float left = 0.0f;
	float right = (float)WINCX;
	float bottom = (float)WINCY;
	float top = 0.0f;

	float nearPlane = 0.0f;
	float farPlane = 1.0f;

	D3DXMATRIX orthoProjectionMatrix;
	D3DXMatrixOrthoOffCenterLH(&orthoProjectionMatrix, left, right, bottom, top, nearPlane, farPlane);

	pGraphicDev->SetTransform(D3DTS_PROJECTION, &orthoProjectionMatrix);

	// 직교투영 적용

	for (auto& iter : m_RenderGroup[RENDER_UI])
		iter->Render_GameObject();


	_matrix projMatrix;

	projMatrix.PerspectiveFovLH(D3DXToRadian(60.f), (_float)WINCX / WINCY, 1.f, 1000.f);
	
	_matrix* viewMatrix = nullptr;
	if (Get_Player() != nullptr)
		viewMatrix = dynamic_cast<CCamera*>(Get_Player()->Get_Component(L"Player_Camera", ID_UPDATE))->Get_Camera_ViewMatrix();

	if (viewMatrix != nullptr)
		pGraphicDev->SetTransform(D3DTS_VIEW, viewMatrix);
	// 원근투영 적용
	// 플레이어 카메라의 뷰행렬을 디바이스에 등록

}

void CRenderer::Free(void)
{
	Clear_RenderGroup();
}
