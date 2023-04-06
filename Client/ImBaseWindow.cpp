#include "ImBaseWindow.h"



CImBaseWindow::CImBaseWindow(LPDIRECT3DDEVICE9 pGraphicDev)
	:CImWindow(pGraphicDev)
{
}

CImBaseWindow::~CImBaseWindow()
{
}

HRESULT CImBaseWindow::Ready_ImWindow()
{
	return S_OK;
}

_int CImBaseWindow::Update(float fTimeDelta)
{
	return 0;
}

CImBaseWindow * CImBaseWindow::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CImBaseWindow* pInstance = new CImBaseWindow(pGraphicDev);

	if (FAILED(pInstance->Ready_ImWindow()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CImBaseWindow::Free(void)
{
	__super::Free();
}
