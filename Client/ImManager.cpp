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

	//_vec3 tmp = Picking_OnTerrain(g_hWnd);
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



Ray CImManager::CalcPickingRay(_int x, _int y)
{
	_float px = 0.f;
	_float py = 0.f;

	D3DVIEWPORT9 vp;
	m_pGraphicDev->GetViewport(&vp);

	_matrix proj;
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &proj);

	px = (((2.f * x) / vp.Width) - 1.0f) / proj(0, 0);
	py = (((-2.f * y) / vp.Height) + 1.0f) / proj(1, 1);

	Ray ray;
	ray._origin = _vec3(0.f, 0.f, 0.f);
	ray._direction = _vec3(px, py, 1.f);

	return ray;
}

_bool CImManager::MouseClickRay(HWND hWnd, /*Out*/ Ray& ray)
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		POINT	ptMouse{};
		GetCursorPos(&ptMouse);
		ScreenToClient(g_hWnd, &ptMouse);
		ray = CalcPickingRay(ptMouse.x, ptMouse.y);

		_matrix		matProj;
		m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);
		D3DXMatrixInverse(&matProj, 0, &matProj);

		//  투영 -> 뷰 스페이스

		return true;
	}
	return false;
}

void CImManager::TransformRay(Ray * ray, _matrix * T)
{
	// 광선의 원점을 변환한다. w=1.
	D3DXVec3TransformCoord(
		&ray->_origin,
		&ray->_origin,
		T);

	// 광선의 방향을 변환한다. w=0.
	D3DXVec3TransformNormal(
		&ray->_direction,
		&ray->_direction,
		T);

	// 방향을 정규화한다.
	D3DXVec3Normalize(&ray->_direction, &ray->_direction);
}

_bool CImManager::IntersectRayMesh(const Ray & ray, ID3DXMesh * mesh, _matrix & worldMatrix, DWORD & faceIndex)
{
	_bool hit = false;
	DWORD numFaces = mesh->GetNumFaces();
	IDirect3DVertexBuffer9* vertexBuffer = nullptr;
	IDirect3DIndexBuffer9* indexBuffer = nullptr;
	_vec3* vertices = nullptr;
	DWORD* indices = nullptr;
	_float u, v, dist;
	_float closestDist = FLT_MAX;

	mesh->GetVertexBuffer(&vertexBuffer);
	mesh->GetIndexBuffer(&indexBuffer);

	vertexBuffer->Lock(0, 0, (void**)&vertices, D3DLOCK_READONLY);
	indexBuffer->Lock(0, 0, (void**)&indices, D3DLOCK_READONLY);

	for (DWORD i = 0; i < numFaces; ++i)
	{
		_vec3 v0 = vertices[indices[3 * i]];
		_vec3 v1 = vertices[indices[3 * i + 1]];
		_vec3 v2 = vertices[indices[3 * i + 2]];

		D3DXVec3TransformCoord(&v0, &v0, &worldMatrix);
		D3DXVec3TransformCoord(&v1, &v1, &worldMatrix);
		D3DXVec3TransformCoord(&v2, &v2, &worldMatrix);

		if (D3DXIntersectTri(&v0, &v1, &v2, &ray._origin, &ray._direction, &u, &v, &dist))
		{
			if (dist < closestDist)
			{
				hit = true;
				closestDist = dist;
				faceIndex = i;
			}
		}
	}

	vertexBuffer->Unlock();
	indexBuffer->Unlock();
	vertexBuffer->Release();
	indexBuffer->Release();

	return hit;
}