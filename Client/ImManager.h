#pragma once

#include "Include.h"

BEGIN(Engine)

class CFloorTex;
class CTransform;
class CPickingSphere;

END

class CImWindow;

class CImManager
{
	DECLARE_SINGLETON(CImManager)
public:
	CImManager();
	~CImManager();

	HRESULT Ready_IMGUI(LPDIRECT3DDEVICE9 pGraphicDev);
	void Update(_float fTimeDelta);
	void Render(LPDIRECT3DDEVICE9 pGraphicDev);
	void Release();

private:
	_bool Compute_RayCastHitFloor(_vec3* result, const Ray* pRay);

	Ray CalcRaycast(POINT ptMouse);
	POINT GetMousePos();

	_vec3 PickingFloor();
	_bool PickingWall(class CWall* pWall);

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