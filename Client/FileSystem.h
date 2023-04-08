#pragma once

#include "Include.h"

class CFileSystem
{
public:
	CFileSystem();
	~CFileSystem();

	static wstring strToWStr(const string& str); 
	static string wstrToStr(const wstring& wstr);
	static string FileNameFromPath(IN const string& strFilePathName);
	static wstring PathRemoveFileSpec(IN const wstring& FilePath);
	static wstring GetCurDirectory();
	static void Save(const TCHAR* path);
	static void Load(const TCHAR* path);
};