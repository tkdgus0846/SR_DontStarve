#pragma once

#include "Include.h"
#include "ImWindow.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "imgui.h"

BEGIN(Engine)

class CTerrainTex;
class CTransform;

END

class CImManager
{
	DECLARE_SINGLETON(CImManager)
public:
	CImManager();
	~CImManager();

	HRESULT Ready_IMGUI(LPDIRECT3DDEVICE9 pGraphicDev);
	void Update(float fTimeDelta);
	void Render(LPDIRECT3DDEVICE9 pGraphicDev);
	void Release();

public:
	void PickingOnMesh(HWND hWnd, ID3DXMesh* pMesh);
private:
	Ray CalcPickingRay(int x, int y);
	void TransformRay(Ray* ray, _matrix* T);
	bool IntersectRayMesh(const Ray& ray, ID3DXMesh* mesh, _matrix& worldMatrix, DWORD& faceIndex);

public:
	void AddList(CImWindow* pImWindow)
	{
		NULL_CHECK(pImWindow);
		m_vecImWindow.push_back(pImWindow);
	}

private:
	LPDIRECT3DDEVICE9 m_pGraphicDev;
	vector<CImWindow*> m_vecImWindow;
};