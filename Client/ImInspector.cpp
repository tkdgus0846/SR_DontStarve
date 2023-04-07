#include "ImInspector.h"

CImInspector::CImInspector(LPDIRECT3DDEVICE9 pGraphicDev)
	:CImWindow(pGraphicDev)
{
}

CImInspector::~CImInspector()
{
}

HRESULT CImInspector::Ready_ImWindow()
{
	return S_OK;
}

_int CImInspector::Update(float fTimeDelta)
{
	ImGui::Begin("Inspector");
	ImGui::End();
	return 0;
}

CImInspector * CImInspector::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CImInspector* pInstance = new CImInspector(pGraphicDev);

	if (FAILED(pInstance->Ready_ImWindow()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CImInspector::Free(void)
{
	__super::Free();
}
