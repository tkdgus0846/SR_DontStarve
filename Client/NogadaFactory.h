#pragma once

#include "Include.h"

BEGIN(Engine)
	class CGameObject;
END

class CMonster;

class CNogadaFactory
{
	DECLARE_SINGLETON(CNogadaFactory)
public:
	CNogadaFactory();
	~CNogadaFactory();

public:
	HRESULT		Ready_CNogadaFactory(LPDIRECT3DDEVICE9 pGraphicDev);
	void Release();
	CGameObject* CreateObj(OBJ_TYPE eType, const char* tag, _vec3 vPos ={ 0.f, 0.f, 0.f });

	CGameObject*Find_Obj(const char * pTag);

private:
	void InsertObj(const char* tag, CGameObject* pObj)
	{
		m_mapTag.insert({ tag , pObj });
	}

private:
	LPDIRECT3DDEVICE9	m_pGraphicDev;
	map<const char*, CGameObject*> m_mapTag;
};

#define FACTORY CNogadaFactory::GetInstance()