#include "SkillUI.h"
#include "Export_Function.h"

CSkillUI::CSkillUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev)
{
}

CSkillUI::~CSkillUI()
{
}

HRESULT CSkillUI::Add_Component()
{
	return S_OK;
}

HRESULT CSkillUI::Ready_GameObject(void)
{
	return S_OK;
}

_int CSkillUI::Update_GameObject(const _float & fTimeDelta)
{
	return 0;
}

void CSkillUI::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CSkillUI::Render_GameObject(void)
{
	Set_ViewMatrix_UI();
	__super::Render_GameObject();
}

CSkillUI * CSkillUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSkillUI* pInstance = new CSkillUI(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CSkillUI::Free(void)
{
	__super::Free();
}
