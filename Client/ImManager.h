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
	// x,y ��ǥ�� ���� ������ ����� �޼���
	Ray CalcPickingRay(_int x, _int y);

	// ������ T��ķ� �ٲ��ִ� �޼���
	void TransformRay(Ray* ray, _matrix* T);

	// �޽��� ������ �浹�ߴ��� �˻��ؼ� true, false��ȯ
	_bool IntersectRayMesh(const Ray& ray, ID3DXMesh* mesh, _matrix& worldMatrix, DWORD& faceIndex);

	// ���콺 Ŭ�� ��ǥ�� ���� ������ ����� �޼���
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