#include "ImManager.h"

IMPLEMENT_SINGLETON(CImManager)

CImManager::CImManager()
{
}


CImManager::~CImManager()
{
	Release();
}

void CImManager::Update(float fTimeDelta)
{
	for (auto& iter: m_vecImWindow)
	{
		int iResult = iter->Update(fTimeDelta);
	}
}

void CImManager::Render(LPDIRECT3DDEVICE9 pGraphicDev)
{
	pGraphicDev->SetRenderState(D3DRS_ZENABLE, FALSE);
	pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	pGraphicDev->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	pGraphicDev->SetRenderState(D3DRS_ZENABLE, TRUE);
	pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pGraphicDev->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);
}

void CImManager::Release()
{
	for_each(m_vecImWindow.begin(), m_vecImWindow.end(), Safe_Delete<CImWindow*>);
}


