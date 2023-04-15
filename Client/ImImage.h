#pragma once
#include "ImWindow.h"
#include "Factory.h"
#include "FileSystem.h"

class ImImage :
	public CImWindow
{
public:
	ImImage(LPDIRECT3DDEVICE9 pGraphicDev);
	~ImImage();

	virtual _int Update(float fTimeDelta) override;
	void	Set_Tag(wstring wstr);
	void	Set_Tag(string str);
	void	Set_Factory(CFactory* pFactory) 
	{
		m_pFactory = pFactory;
	}

public:
	static ImImage* Create(LPDIRECT3DDEVICE9 pGraphicDev, CFactory* m_pFactory);
	virtual void Free(void);

private:
	const _tchar* m_wTag = nullptr;
	const char* m_sTag = nullptr;
	CFactory* m_pFactory;
	CGameObject* m_pObj;
};

