#pragma once

#include "Include.h"

__interface ISaveTarget
{
public:
	virtual void Save(HANDLE hFile, DWORD& dwByte) PURE;

	virtual void Load(HANDLE hFile, DWORD& dwByte) PURE;
};