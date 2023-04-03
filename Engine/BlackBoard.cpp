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

void CBlackBoard::Add_Type(const _tchar * pTypename, const _int & iType)
{
	auto iter = find_if(m_mapInt.begin(), m_mapInt.end(), CTag_Finder(pTypename));

	if (iter == m_mapInt.end())
		m_mapInt.emplace(pTypename, iType);
}

void CBlackBoard::Add_Type(const _tchar * pTypename, const _float & fType)
{
	auto iter = find_if(m_mapFloat.begin(), m_mapFloat.end(), CTag_Finder(pTypename));

	if (iter == m_mapFloat.end())
		m_mapFloat.emplace(pTypename, fType);
}

void CBlackBoard::Add_Type(const _tchar * pTypename, const _bool & bType)
{
	auto iter = find_if(m_mapBool.begin(), m_mapBool.end(), CTag_Finder(pTypename));

	if (iter == m_mapBool.end())
		m_mapBool.emplace(pTypename, bType);
}

HRESULT CBlackBoard::Get_Type(const _tchar * pTypename, _int * pType)
{
	auto iter = find_if(m_mapInt.begin(), m_mapInt.end(), CTag_Finder(pTypename));

	if (iter == m_mapInt.end())
	{
		pType = nullptr;
		return E_FAIL;
	}

	pType = &iter->second;
	return S_OK;
}

HRESULT CBlackBoard::Get_Type(const _tchar * pTypename, _float * pType)
{
	auto iter = find_if(m_mapFloat.begin(), m_mapFloat.end(), CTag_Finder(pTypename));

	if (iter == m_mapFloat.end())
	{
		pType = nullptr;
		return E_FAIL;
	}

	*pType = iter->second;
	return S_OK;
}

HRESULT CBlackBoard::Get_Type(const _tchar * pTypename, _bool * pType)
{
	auto iter = find_if(m_mapBool.begin(), m_mapBool.end(), CTag_Finder(pTypename));

	if (iter == m_mapBool.end())
	{
		pType = nullptr;
		return E_FAIL;
	}

	pType = &iter->second;
	return S_OK;
}