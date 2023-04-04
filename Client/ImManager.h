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
	// x,y 좌표에 대해 광선을 만드는 메서드
	Ray CalcPickingRay(_int x, _int y);

	// 광선을 T행렬로 바꿔주는 메서드
	void TransformRay(Ray* ray, _matrix* T);

	// 메쉬와 광선이 충돌했는지 검사해서 true, false반환
	_bool IntersectRayMesh(const Ray& ray, ID3DXMesh* mesh, _matrix& worldMatrix, DWORD& faceIndex);

	// 마우스 클릭 좌표에 대해 광선을 만드는 메서드
	_bool MouseClickRay(HWND hWnd, Ray& ray);

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