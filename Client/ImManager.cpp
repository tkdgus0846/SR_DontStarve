#include "ImManager.h"
#include "ImWindow.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "imgui.h"
#include "Export_Function.h"
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
	m_pGraphicDev = pGraphicDev;
	m_pGraphicDev->AddRef();

	return S_OK;
}

void CImManager::Update(_float fTimeDelta)
{
	for (auto& iter: m_vecImWindow)
	{
		_int iResult = iter->Update(fTimeDelta);
	}
	_vec3 tmp = GetRayFromMouse();
	
	//cout << (_int)tmp.x << "\t" << (_int)tmp.z << endl;
}

void CImManager::Render(LPDIRECT3DDEVICE9 pGraphicDev)
{
	/*pGraphicDev->SetRenderState(D3DRS_ZENABLE, FALSE);
	pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	pGraphicDev->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);*/
	
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

void CImManager::Release()
{
	Safe_Release(m_pGraphicDev);
	for_each(m_vecImWindow.begin(), m_vecImWindow.end(), Safe_Delete<CImWindow*>);
}




_vec3 CImManager::GetRayFromMouse()
{
	if (GetAsyncKeyState(VK_RBUTTON))
	{
		POINT pt{};
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);
		int mouseX = pt.x, mouseY = pt.y;

		D3DVIEWPORT9 viewport; // 뷰포트 정보
		m_pGraphicDev->GetViewport(&viewport); // 뷰포트 정보 가져오기

		D3DXMATRIX matProjection, matView, matWorld;
		m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProjection); // 프로젝션 행렬 가져오기
		m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView); // 뷰 행렬 가져오기
		D3DXMatrixIdentity(&matWorld); // 월드 행렬을 단위 행렬로 설정

		_vec3 vecScreen(mouseX, mouseY, 0.0f);
		_vec3 vecNear, vecFar;

		// 스크린 좌표를 월드 좌표로 변환
		D3DXVec3Unproject(&vecNear, &vecScreen, &viewport, &matProjection, &matView, &matWorld);

		vecScreen.z = 1.0f;
		D3DXVec3Unproject(&vecFar, &vecScreen, &viewport, &matProjection, &matView, &matWorld);

		// 방향 벡터 계산
		_vec3 vecDirection = vecFar - vecNear;
		vecDirection.Normalize();

		return vecDirection;
	}
}