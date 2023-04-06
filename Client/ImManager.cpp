#include "ImManager.h"
#include "ImWindow.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "imgui.h"
#include "Export_Function.h"
#include "Floor.h"
#include "Wall.h"

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
	for (auto& iter : m_vecImWindow)
	{
		_int iResult = iter->Update(fTimeDelta);
	}
	if (PickingFloor()) {}
	//	cout << "gd" << endl;
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

_bool CImManager::Compute_RayCastHitFloor(_vec3 * result, const Ray* pRay)
{
	_bool success = false;
	_float u, v;
	_float dist = FLT_MAX;
	_float distTemp = 0.f;
	_vec3 vFloorArr[VTXCNTX * VTXCNTZ];
	_ulong	dwIndex = 0;

	for (_ulong i = 0; i < VTXCNTZ; ++i)
	{
		for (_ulong j = 0; j < VTXCNTX; ++j)
		{
			dwIndex = i * VTXCNTX + j;

			vFloorArr[dwIndex] = {
				_float(j * VTXITV),
				0.f,
				_float(i * VTXITV) };
		}
	}

	_vec3 v0, v1, v2;

	for (int i = 0; i < VTXCNTZ - 1; i++)
	{
		for (int j = 0; j < VTXCNTX - 1; j++)
		{
			DWORD dwIndex = i * VTXCNTX + j;
			_bool tempSuccess;

			v0 = vFloorArr[dwIndex + VTXCNTX];
			v1 = vFloorArr[dwIndex + VTXCNTX + 1];
			v2 = vFloorArr[dwIndex + 1];

			tempSuccess = D3DXIntersectTri(&v0, &v1, &v2
				, (const D3DXVECTOR3*)(&pRay->vOrigin)
				, (const D3DXVECTOR3*)(&pRay->vDirection)
				, &u, &v, &distTemp);

			if (tempSuccess && (dist > distTemp))
			{
				*result = v0 + u*(v1 - v0) + v * (v2 - v0);
				dist = distTemp;
				success = tempSuccess;
			}

			v0 = vFloorArr[dwIndex + VTXCNTX];
			v1 = vFloorArr[dwIndex + 1];
			v2 = vFloorArr[dwIndex];

			tempSuccess = D3DXIntersectTri(&v0, &v1, &v2
				, (const D3DXVECTOR3*)(&pRay->vOrigin)
				, (const D3DXVECTOR3*)(&pRay->vDirection)
				, &u, &v, &distTemp);

			if (tempSuccess && (dist > distTemp))
			{
				*result = v0 + u*(v1 - v0) + v * (v2 - v0);
				dist = distTemp;
				success = tempSuccess;
			}
		}
	}

	return success;
}



Ray CImManager::CalcRaycast(POINT ptMouse)
{
	Ray ray;
	_vec3 vMouse;
	
	// 뷰포트 -> 투영
	D3DVIEWPORT9		ViewPort;
	ZeroMemory(&ViewPort, sizeof(D3DVIEWPORT9));
	m_pGraphicDev->GetViewport(&ViewPort);
	vMouse.x = ptMouse.x / (ViewPort.Width * 0.5f) - 1.f;
	vMouse.y = ptMouse.y / -(ViewPort.Height * 0.5f) + 1.f;
	vMouse.z = 0.f;

	//  투영 -> 뷰 스페이스
	_matrix		matProj;
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);
	D3DXMatrixInverse(&matProj, 0, &matProj);
	D3DXVec3TransformCoord(&vMouse, &vMouse, &matProj);

	// 뷰 스페이스 -> 월드
	_matrix		matView;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matView, 0, &matView);
	ray.vOrigin = { 0.f,0.f,0.f };
	ray.vDirection = vMouse - ray.vOrigin;

	D3DXVec3TransformCoord(&ray.vOrigin, &ray.vOrigin, &matView);
	D3DXVec3TransformNormal(&ray.vDirection, &ray.vDirection, &matView);

	return ray;
}

POINT CImManager::GetMousePos()
{
	POINT ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	return ptMouse;
}

_vec3 CImManager::PickingFloor()
{
	POINT ptMouse = GetMousePos();

	Ray ray = CalcRaycast(ptMouse);
	//cout << ray.vDirection.x << "\t" << ray.vDirection.y << endl;

	_vec3 result;
	bool hit = Compute_RayCastHitFloor(&result, &ray);


	return result;
}