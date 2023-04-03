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

	HRESULT Get_Type(const _tchar* pTypename, _int* pType);
	HRESULT Get_Type(const _tchar* pTypename, _float* pType);
	HRESULT Get_Type(const _tchar* pTypename, _bool* pType);

private:
	map<const _tchar*, _int>		m_mapInt;
	map<const _tchar*, _float>		m_mapFloat;
	map<const _tchar*, _bool>		m_mapBool;
};

END