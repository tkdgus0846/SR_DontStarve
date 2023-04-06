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
	_int Update(_float fTimeDelta);
	void Render(LPDIRECT3DDEVICE9 pGraphicDev);
	void Release();

public:
	void AddList(CImWindow* pImWindow)
	{
		NULL_CHECK(pImWindow);
		m_vecImWindow.push_back(pImWindow);
	}

private:
	vector<CImWindow*> m_vecImWindow;
};