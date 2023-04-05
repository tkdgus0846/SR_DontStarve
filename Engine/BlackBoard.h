#pragma once

BEGIN(Engine)

class CGameObject;
class CBlackBoard
{
public:
	explicit CBlackBoard();
	explicit CBlackBoard(const CBlackBoard& rhs);
	~CBlackBoard();

public:
	HRESULT Add_Type(const _tchar* pTypename, const _int& iType);
	HRESULT Add_Type(const _tchar* pTypename, const _float& fType);
	HRESULT Add_Type(const _tchar* pTypename, const _bool& bType);
	HRESULT Add_Type(const _tchar* pTypename, const _vec3& vType);
	HRESULT Add_Type(const _tchar* pTypename, CGameObject* pType);

	HRESULT Get_Type(const _tchar* pTypename, _int* pOut);
	HRESULT Get_Type(const _tchar* pTypename, _float* pOut);
	HRESULT Get_Type(const _tchar* pTypename, _bool* pOut);
	HRESULT Get_Type(const _tchar* pTypename, _vec3* pOut);
	HRESULT Get_Type(const _tchar* pTypename, CGameObject* pOut);

private:
	map<const _tchar*, _int>			m_mapInt;
	map<const _tchar*, _float>			m_mapFloat;
	map<const _tchar*, _bool>			m_mapBool;
	map<const _tchar*, _vec3>			m_mapVec;
	map<const _tchar*, CGameObject*>	m_mapGameObject;
};

END