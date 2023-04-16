#pragma once

#include "Include.h"
#include "GameObject.h"

// Ŭ������ ������ ������ ������ ������.
typedef CGameObject* (*CreateObjectFunc)(LPDIRECT3DDEVICE9);
typedef struct tagClassInfo
{
	CreateObjectFunc	CreateFunc;
	wstring				TextureKey;
}ClassInfo, CInfo;

class CFactory
{
protected:
	CFactory();
	virtual ~CFactory();

	HRESULT Ready_TileFactory(LPDIRECT3DDEVICE9 pGraphicDev);
	void Release();

protected:
	virtual void Register(const wstring& objectType, CreateObjectFunc createFunc);

public:
	CGameObject*	CreateObject(const wstring& objectType);
	wstring			FindTagByTextureKey(wstring				TextureKey);
	wstring			FindTextureKeyByTag(wstring Tag);

	const vector<wstring>& GetWTag() { return m_vecWstrTag; }
	const vector<string>& GetSTag() { return m_vecStrTag; }

protected:
	map<wstring, CInfo> m_creationMap;
	vector<wstring> m_vecWstrTag;
	vector<string>	m_vecStrTag;
	LPDIRECT3DDEVICE9 m_pGraphicDev;
};