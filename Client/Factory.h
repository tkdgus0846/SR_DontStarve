#pragma once

#include "Include.h"
#include "GameObject.h"

class CFactory
{
protected:
	CFactory();
	virtual ~CFactory();

	HRESULT Ready_TileFactory(LPDIRECT3DDEVICE9 pGraphicDev);
	void Release();

protected:
	typedef CGameObject* (*CreateObjectFunc)(LPDIRECT3DDEVICE9);
	void Register(const wstring& objectType, CreateObjectFunc createFunc);

public:
	CGameObject* CreateObject(const wstring& objectType);

protected:
	map<wstring, CreateObjectFunc> m_creationMap;
	LPDIRECT3DDEVICE9 m_pGraphicDev;
};