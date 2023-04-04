#pragma once

#include "Include.h"


BEGIN(Engine)

class CTerrainTex;
class CTransform;

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

public:


	void		IndexTranslation2DTo1D(_ulong Index, _ulong row, _ulong col);
	void		IndexTranslation1DTo2D(_ulong Index, _ulong row, _ulong col);

private:     
	_vec3 GetRayFromMouse();

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