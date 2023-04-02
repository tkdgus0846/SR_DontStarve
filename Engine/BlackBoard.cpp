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
	auto iter = find_if(m_matInt.begin(), m_matInt.end(), CTag_Finder(pTypename));

	if (iter == m_matInt.end())
		m_matInt.emplace(pTypename, iType);
}

void CBlackBoard::Add_Type(const _tchar * pTypename, const _float & fType)
{
	auto iter = find_if(m_matFloat.begin(), m_matFloat.end(), CTag_Finder(pTypename));

	if (iter == m_matFloat.end())
		m_matFloat.emplace(pTypename, fType);
}

void CBlackBoard::Add_Type(const _tchar * pTypename, const _bool & bType)
{
	auto iter = find_if(m_matBool.begin(), m_matBool.end(), CTag_Finder(pTypename));

	if (iter == m_matBool.end())
		m_matBool.emplace(pTypename, bType);
}

void CBlackBoard::Get_Type(const _tchar * pTypename, _int * pType)
{
	auto iter = find_if(m_matInt.begin(), m_matInt.end(), CTag_Finder(pTypename));

	if (iter == m_matInt.end())
		pType = nullptr;

	pType = &iter->second;
}

void CBlackBoard::Get_Type(const _tchar * pTypename, _float * pType)
{
	auto iter = find_if(m_matFloat.begin(), m_matFloat.end(), CTag_Finder(pTypename));

	if (iter == m_matFloat.end())
		pType = nullptr;

	pType = &iter->second;
}

void CBlackBoard::Get_Type(const _tchar * pTypename, _bool * pType)
{
	auto iter = find_if(m_matBool.begin(), m_matBool.end(), CTag_Finder(pTypename));

	if (iter == m_matBool.end())
		pType = nullptr;

	pType = &iter->second;
}