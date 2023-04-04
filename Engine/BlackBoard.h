#pragma once

/*
블랙보드는 ai호출자가 가지고 있는 자료형들을 저장하는 클래스이다.
비헤비어트리의 구성요소들(시퀀스나 셀렉트나 태스크 등)은 이 블랙보드의 자료형을 참조해서
기능을 수행하거나 블랙보드의 자료형 값들을 변경하는 작업을 진행한다.

읽다가 모르는 사항이 있을 경우 주성환 한테 물어보세요
*/

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

	HRESULT Get_Type(const _tchar* pTypename, _int* pOut);
	HRESULT Get_Type(const _tchar* pTypename, _float* pOut);
	HRESULT Get_Type(const _tchar* pTypename, _bool* pOut);

private:
	map<const _tchar*, _int>		m_mapInt;
	map<const _tchar*, _float>		m_mapFloat;
	map<const _tchar*, _bool>		m_mapBool;
};

END