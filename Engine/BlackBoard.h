#pragma once

/*
������� aiȣ���ڰ� ������ �ִ� �ڷ������� �����ϴ� Ŭ�����̴�.
������Ʈ���� ������ҵ�(�������� ����Ʈ�� �½�ũ ��)�� �� �������� �ڷ����� �����ؼ�
����� �����ϰų� �������� �ڷ��� ������ �����ϴ� �۾��� �����Ѵ�.

�дٰ� �𸣴� ������ ���� ��� �ּ�ȯ ���� �������
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