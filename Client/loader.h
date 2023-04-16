#pragma once


#include "GameObject.h"
#include "Serializable.h"

class CLoader
{
	DECLARE_SINGLETON(CLoader)
private:
	CLoader();
	~CLoader();

public:
	void Ready_Loader(LPDIRECT3DDEVICE9 pGraphicDev);

	CGameObject* Load(HANDLE hFile, DWORD& dwByte, const _tchar* tag);
	
private:
	void Release();
	HRESULT	Insert_SaveTarget(const _tchar * pObjTag, ISerializable* pTile);
	ISerializable * Find_SaveTarget(const _tchar * pObjTag);

private:
	LPDIRECT3DDEVICE9 m_pGraphicDev;
	map<const _tchar*, ISerializable*> m_mapSaveTarget;
};

#define LOADER CLoader::GetInstance()