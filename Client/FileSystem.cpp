#include "FileSystem.h"
#include <locale>
#include <codecvt>

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

string CFileSystem::FileNameFromPath(const string& strFilePathName)
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
