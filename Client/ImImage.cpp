#include "ImImage.h"
#include "Export_Function.h"
ImImage::ImImage(LPDIRECT3DDEVICE9 pGraphicDev)
	: CImWindow(pGraphicDev)
	, m_pFactory(nullptr)
{
}

ImImage::~ImImage()
{
}

_int ImImage::Update(float fTimeDelta)
{
	if (!IsEnable())
		return 0;

	if (!m_pFactory)
		return 0;

	if (!m_pObj)
		return 0;

	CTexture* pTexture = m_pObj->Get_Texture();

	if (pTexture)
		ImGui::Image((void*)pTexture->Get_TextureCom(), ImVec2(100.f, 100.f));
}

void ImImage::Set_Tag(wstring wstr)
{
	m_wTag = wstr.c_str();
	m_sTag = CFileSystem::wstrToStr(wstr).c_str();
	Safe_Release(m_pObj);
	m_pObj = m_pFactory->CreateObject(m_wTag);
}

void ImImage::Set_Tag(string str)
{
	m_sTag = str.c_str();
	m_wTag = CFileSystem::strToWStr(str).c_str();
	Safe_Release(m_pObj);
	m_pObj = m_pFactory->CreateObject(m_wTag);
}

ImImage * ImImage::Create(LPDIRECT3DDEVICE9 pGraphicDev, CFactory* pFactory)
{
	ImImage* pInstance = new ImImage(pGraphicDev);

	if (FAILED(pInstance->Ready_ImWindow()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	pInstance->Set_Factory(pFactory);
	return pInstance;
}

void ImImage::Free(void)
{
	Safe_Release(m_pObj);
	__super::Free();
}