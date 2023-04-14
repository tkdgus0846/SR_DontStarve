#pragma once

#include "Include.h"

BEGIN(Engine)
	class CGameObject;
	class CTexture;
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
	CGameObject* GetGameObj(const char* tag);
	CTexture*	 GetTexture(const char* tag);
	vector<const char*>& GetTagVec(OBJ_TYPE eType)
	{
		return m_vecTag[eType];
	}
	_int Size(OBJ_TYPE eType) {
		return m_vecObj
			[eType].size();
	}
	CGameObject* CreateObj(const char* tag);

private:
	CGameObject* Find_Obj(const char* tag);
	void Push_Back(OBJ_TYPE eType, const char* tag, CGameObject* pObj)
	{
		m_vecObj[eType].push_back(pObj);
		m_vecTag[eType].push_back(tag);
	}

private:
	LPDIRECT3DDEVICE9		m_pGraphicDev;
	vector<CGameObject*>	m_vecObj[OBJ_END];
	vector<const char*>		m_vecTag[OBJ_END];
};

#define FACTORY CNogadaFactory::GetInstance()