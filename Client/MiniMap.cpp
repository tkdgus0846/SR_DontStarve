#include "MiniMap.h"
#include "Export_Function.h"

CMiniMap::CMiniMap(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUI(pGraphicDev)
{
}

CMiniMap::~CMiniMap()
{
}

HRESULT CMiniMap::Add_Component()
{
	CRcTex* RcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(RcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", RcTex });

	CTexture* Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"CrossHair_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"CrossHair_Texture", Texture });

	CAnimation* Ani = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(Ani, E_FAIL);

	Ani->BindAnimation(ANIM_IDLE, Texture, 0.1f);
	Ani->SelectState(ANIM_IDLE);
	m_uMapComponent[ID_ALL].insert({ L"Animation", Ani });

	return S_OK;
}

HRESULT CMiniMap::Ready_GameObject(void)
{
	__super::Ready_GameObject();

	return S_OK;
}

_int CMiniMap::Update_GameObject(const _float & fTimeDelta)
{
	__super::Update_GameObject(fTimeDelta);

	return 0;
}

void CMiniMap::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CMiniMap::Render_GameObject(void)
{
	Set_VeiwMatrix_UI();

	__super::Render_GameObject();
}

void CMiniMap::Set_VeiwMatrix_UI()
{
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);

	D3DXMatrixScaling(&matView, 25.f, 25.f, 0.f);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
}

CMiniMap * CMiniMap::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMiniMap* pInstance = new CMiniMap(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CMiniMap::Free(void)
{
	__super::Free();
}
