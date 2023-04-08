#include "FileSystem.h"
#include <locale>
#include <codecvt>
#include "MyMap.h"
#include "Export_Function.h"

CFileSystem::CFileSystem()
{
}


CFileSystem::~CFileSystem()
{
}

string CFileSystem::wstrToStr(const wstring & wstr)
{
	wstring_convert<codecvt_utf8<wchar_t>, wchar_t> converter;
	return converter.to_bytes(wstr);
}

wstring CFileSystem::strToWStr(const string & str)
{
	wstring_convert<codecvt_utf8<wchar_t>, wchar_t> converter;
	return converter.from_bytes(str);
}

string CFileSystem::FileNameFromPath(IN const string& strFilePathName)
{
	string strFileName;
	size_t lastSlashPosition = strFilePathName.find_last_of("\\/");
	if (lastSlashPosition != std::string::npos) {
		strFileName = strFilePathName.substr(lastSlashPosition + 1);
	}
	else {
		strFileName = strFilePathName;
	}
	return strFileName;
}

wstring  CFileSystem::PathRemoveFileSpec(IN const wstring& filePath)
{
	size_t lastSlashPosition = filePath.find_last_of(L"\\/");
	if (lastSlashPosition != wstring::npos) {
		return filePath.substr(0, lastSlashPosition);
	}
	else {
		return filePath;
	}
}

wstring CFileSystem::GetCurDirectory()
{
	_tchar buffer[MAX_PATH];
	DWORD length = GetCurrentDirectory(MAX_PATH, buffer);
	wstring tmp(buffer);
	return tmp;
}

void CFileSystem::Save(const TCHAR* path)
{
	HANDLE		hFile = CreateFile(path,		// ���� ��ο� �̸��� ���
		GENERIC_WRITE,			// ���� ���� ���(���� ����), GENERIC_READ(�б� ����)
		NULL,					// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ����� ���� �� �� �㰡�ϴ� �Ϳ� ���� ����, NULL�� �����ϸ� �������� �ʰڴٴ� �ǹ�
		NULL,					// ���� �Ӽ�, NULL�� ��� �⺻������ ���� ���¸� ����
		CREATE_ALWAYS,			// ���� ���, �ش� ������ ��� �۾��� �� ������, ���� ���� ������ ����(CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXISTING : ������ ���� ��쿡�� ����)
		FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�, FILE_ATTRIBUTE_NORMAL �ƹ��� �ӽ� ���� �Ϲ����� ���� ����
		NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����, �Ⱦ��ϱ� NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Save File", L"Fail", MB_OK);
		return;
	}
	DWORD		dwByte = 0;

	dynamic_cast<CMyMap*>(Get_GameObject(LAYER_ENVIRONMENT, L"Map"))->WriteMapFile(hFile, dwByte);

	// ���� �Ҹ�
	CloseHandle(hFile);
}

void CFileSystem::Load(const TCHAR* path)
{
	HANDLE		hFile = CreateFile(path,		// ���� ��ο� �̸��� ���
		GENERIC_READ,			// ���� ���� ���(���� ����), GENERIC_READ(�б� ����)
		NULL,					// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ����� ���� �� �� �㰡�ϴ� �Ϳ� ���� ����, NULL�� �����ϸ� �������� �ʰڴٴ� �ǹ�
		NULL,					// ���� �Ӽ�, NULL�� ��� �⺻������ ���� ���¸� ����
		OPEN_EXISTING,			// ���� ���, �ش� ������ ��� �۾��� �� ������, ���� ���� ������ ����(CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXISTING : ������ ���� ��쿡�� ����)
		FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�, FILE_ATTRIBUTE_NORMAL �ƹ��� �ӽ� ���� �Ϲ����� ���� ����
		NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����, �Ⱦ��ϱ� NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Load File", L"Fail", MB_OK);
		return;
	}
	DWORD		dwByte = 0;

	dynamic_cast<CMyMap*>(Get_GameObject(LAYER_ENVIRONMENT, L"Map"))->ReadMapFile(hFile, dwByte);

	// ���� �Ҹ�
	CloseHandle(hFile);
}