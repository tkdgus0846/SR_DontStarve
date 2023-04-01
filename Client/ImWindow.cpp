#include "ImWindow.h"
#include "Export_Function.h"

CImWindow::CImWindow()
{
}

CImWindow::~CImWindow()
{
	
}

HRESULT CImWindow::Ready_ImWindow(CGameObject* pGameObject)
{
	m_pTarget = pGameObject;

	return S_OK;
}

