#include "stdafx.h"
#include "BlackBoard.h"


CBlackBoard::CBlackBoard()
{
}

CBlackBoard::CBlackBoard(const CBlackBoard & rhs)
{
}

CBlackBoard::~CBlackBoard()
{
}

HRESULT CBlackBoard::Add_Type(const _tchar * pTypename, const _int & iType)
{
	auto iter = find_if(m_mapInt.begin(), m_mapInt.end(), CTag_Finder(pTypename));

	if (iter == m_mapInt.end())
	{
		m_mapInt.emplace(pTypename, iType);
		return S_OK;
	}
	return E_FAIL;
}

HRESULT CBlackBoard::Add_Type(const _tchar * pTypename, const _float & fType)
{
	auto iter = find_if(m_mapFloat.begin(), m_mapFloat.end(), CTag_Finder(pTypename));

	if (iter == m_mapFloat.end())
	{
		m_mapFloat.emplace(pTypename, fType);
		return S_OK;
	}
	return E_FAIL;
}

HRESULT CBlackBoard::Add_Type(const _tchar * pTypename, const _bool & bType)
{
	auto iter = find_if(m_mapBool.begin(), m_mapBool.end(), CTag_Finder(pTypename));

	if (iter == m_mapBool.end())
	{
		m_mapBool.emplace(pTypename, bType);
		return S_OK;
	}
	return E_FAIL;
}

HRESULT CBlackBoard::Add_Type(const _tchar* pTypename, const _vec3& vType)
{
	auto iter = find_if(m_mapBool.begin(), m_mapBool.end(), CTag_Finder(pTypename));

	if (iter == m_mapBool.end())
	{
		m_mapBool.emplace(pTypename, vType);
		return S_OK;
	}
	return E_FAIL;
}

HRESULT CBlackBoard::Add_Type(const _tchar* pTypename, CGameObject* pType)
{
	auto iter = find_if(m_mapGameObject.begin(), m_mapGameObject.end(), CTag_Finder(pTypename));

	if (iter == m_mapGameObject.end())
	{
		m_mapGameObject.emplace(pTypename, pType);
		return S_OK;
	}
	return E_FAIL;
}

HRESULT CBlackBoard::Get_Type(const _tchar * pTypename, _int * pOut)
{
	auto iter = find_if(m_mapInt.begin(), m_mapInt.end(), CTag_Finder(pTypename));

	if (iter == m_mapInt.end())
	{
		pOut = nullptr;
		return E_FAIL;
	}

	pOut = &iter->second;
	return S_OK;
}

HRESULT CBlackBoard::Get_Type(const _tchar * pTypename, _float * pOut)
{
	auto iter = find_if(m_mapFloat.begin(), m_mapFloat.end(), CTag_Finder(pTypename));

	if (iter == m_mapFloat.end())
	{
		pOut = nullptr;
		return E_FAIL;
	}

	*pOut = iter->second;
	return S_OK;
}

HRESULT CBlackBoard::Get_Type(const _tchar * pTypename, _bool * pOut)
{
	auto iter = find_if(m_mapBool.begin(), m_mapBool.end(), CTag_Finder(pTypename));

	if (iter == m_mapBool.end())
	{
		pOut = nullptr;
		return E_FAIL;
	}

	pOut = &iter->second;
	return S_OK;
}

HRESULT CBlackBoard::Get_Type(const _tchar* pTypename, _vec3* pOut)
{
	auto iter = find_if(m_mapVec.begin(), m_mapVec.end(), CTag_Finder(pTypename));

	if (iter == m_mapVec.end())
	{
		pOut = nullptr;
		return E_FAIL;
	}

	pOut = &iter->second;
	return S_OK;
}

HRESULT CBlackBoard::Get_Type(const _tchar* pTypename, CGameObject* pOut)
{
	auto iter = find_if(m_mapGameObject.begin(), m_mapGameObject.end(), CTag_Finder(pTypename));

	if (iter == m_mapGameObject.end())
	{
		pOut = nullptr;
		return E_FAIL;
	}

	pOut = iter->second;
	return S_OK;
}