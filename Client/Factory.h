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
	virtual void Register(const wstring& objectType, CreateObjectFunc createFunc);

public:
	CGameObject* CreateObject(const wstring& objectType);
	const vector<wstring>& GetWTag() { return m_vecWstrTag; }
	const vector<string>& GetSTag() { return m_vecStrTag; }

protected:
	map<wstring, CreateObjectFunc> m_creationMap;
	vector<wstring> m_vecWstrTag;
	vector<string>	m_vecStrTag;
	LPDIRECT3DDEVICE9 m_pGraphicDev;
};