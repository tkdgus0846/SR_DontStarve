#pragma once

BEGIN(Engine)

class CBlackBoard
{
public:
	explicit CBlackBoard();
	explicit CBlackBoard(const CBlackBoard& rhs);
	~CBlackBoard();

public:
	void Add_Type(const _tchar* pTypename, const _int& iType);
	void Add_Type(const _tchar* pTypename, const _float& fType);
	void Add_Type(const _tchar* pTypename, const _bool& bType);

	void Get_Type(const _tchar* pTypename, _int* pType);
	void Get_Type(const _tchar* pTypename, _float* pType);
	void Get_Type(const _tchar* pTypename, _bool* pType);

private:
	map<const _tchar*, _int>		m_matInt;
	map<const _tchar*, _float>		m_matFloat;
	map<const _tchar*, _bool>		m_matBool;
};

END