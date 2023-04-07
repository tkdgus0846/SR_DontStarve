#pragma once

#include "ImWindow.h"

class CImTest :
	public CImWindow
{
protected:
	explicit CImTest(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CImTest();

public:
	virtual HRESULT Ready_ImWindow();
	virtual _int Update(float fTimeDelta);
	
	static CImTest* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	// 파일 경로 + 파일명 출력
	//string GetFilePathName() { return m_strFilePathName; }
	// 파일 경로만 출력
	//string GetFilePath() { return m_strFilePath; }
	// 파일 이름만 출력
	//string GetFileName() { return m_strFileName; }

private:
	void FileDialog();

	void Save();
	void Load();

private:
	_bool			m_bOpenButton = false;
	_bool			m_bIsSave = false;
	wstring			m_strFilePathName;
	wstring			m_strFilePath;
	wstring			m_strFileName;

protected:
	virtual void Free(void);
};