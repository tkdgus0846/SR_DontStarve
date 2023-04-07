#include "ImManager.h"
#include "ImWindow.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "imgui.h"
#include "Export_Function.h"
#include "ImInspector.h"

IMPLEMENT_SINGLETON(CImManager)

CImManager::CImManager()
{
}

CImManager::~CImManager()
{
	Release();
}

HRESULT CImManager::Ready_IMGUI(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CImInspector* pInstance = CImInspector::Create(pGraphicDev);

	NULL_CHECK_RETURN(pInstance, E_FAIL);

	m_vecImWindow.push_back(pInstance);

	return S_OK;
}

_int CImManager::Update(_float fTimeDelta)
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	for (auto& iter : m_vecImWindow)
		_int iResult = iter->Update(fTimeDelta);

	ImGui::EndFrame();

	return 0;
}

void CImManager::Render(LPDIRECT3DDEVICE9 pGraphicDev)
{
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

void CImManager::Release()
{
	for (auto iter : m_vecImWindow)
		Safe_Release(iter);

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}