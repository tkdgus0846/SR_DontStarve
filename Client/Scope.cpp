#include "Scope.h"



CScope::CScope(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev)
{
	Set_ObjTag(L"Scope");
}


CScope::~CScope()
{
}

HRESULT CScope::Add_Component()
{/*
	CRcTex* pRcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"BulletBar_Texture", this));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"BulletBar_Texture", pComponent });
	*/
	return S_OK;
}

HRESULT CScope::Ready_GameObject(void)
{
	Ready_GameObject();
	return S_OK;
}

_int CScope::Update_GameObject(const _float & fTimeDelta)
{
	return _int();
}

void CScope::LateUpdate_GameObject(void)
{
}

void CScope::Render_GameObject(void)
{
}

CScope * CScope::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	return nullptr;
}

void CScope::Free(void)
{
}
