#include "SkillUI.h"
#include "Export_Function.h"

CSkillUI::CSkillUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev)
{
	Set_ObjTag(L"SkillUI");
}

CSkillUI::~CSkillUI()
{
}

HRESULT CSkillUI::Add_Component()
{
	m_pRcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(m_pRcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", m_pRcTex });

	CTexture* Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Skill_List_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"Skill_List_Texture", Texture });

	Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"TimeStop_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_arrMap[TIMESTOP] = Texture;

	Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Gravition_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_arrMap[GRAVITION] = Texture;

	Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Tactical_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_arrMap[TACTICAL] = Texture;

	return S_OK;
}

HRESULT CSkillUI::Ready_GameObject(void)
{
	m_vScale = { 112.f, 28.f, 0.f };
	__super::Ready_GameObject();

	return S_OK;
}

_int CSkillUI::Update_GameObject(const _float & fTimeDelta)
{
	Engine::Add_RenderGroup(RENDER_AFTER_ALPHA_UI, this);

	__super::Update_GameObject(fTimeDelta);

	return 0;
}

void CSkillUI::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CSkillUI::Render_GameObject(void)
{
	Set_ViewMatrix_UI(-200.f, -182.f);

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
	Safe_Release(m_pRcTex);

	auto iter = m_arrMap.begin();
	for (; iter < m_arrMap.end(); iter++)
	{
		Safe_Release(*iter);
	}

	__super::Free();
}
