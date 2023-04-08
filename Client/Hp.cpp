#include "Hp.h"
#include "Export_Function.h"
CHp::CHp(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUI(pGraphicDev)
{
}

CHp::~CHp()
{

}

HRESULT CHp::Ready_GameObject(void)
{
	__super::Ready_GameObject();

	return S_OK;
}

_int CHp::Update_GameObject(const _float & fTimeDelta)
{
	if (Engine::Key_Down(DIK_2) && m_iCurrentHp <= 3)
	{
		m_iCurrentHp += 1;
	}
	Engine::Add_RenderGroup(RENDER_ALPHA_UI, this);

	__super::Update_GameObject(fTimeDelta);

	return 0;
}

void CHp::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CHp::Render_GameObject(void)
{
	Set_OrthoProj();

	m_pTextureCom->Set_Texture_Num(m_iCurrentHp);

	m_pGraphicDev->SetTexture(0, nullptr);

	__super::Render_GameObject();
}

HRESULT CHp::Add_Component(void)
{
	for (_int i = 0; i < m_iMaxHp; i++)
	{
		CRcTex* RcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
		NULL_CHECK_RETURN(RcTex, E_FAIL);
		
		m_pTextureCom = nullptr;
		m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Hp_Texture", this));
		NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	}

	//CAnimation* Ani = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	//NULL_CHECK_RETURN(Ani, E_FAIL);

	//Ani->BindAnimation(ANIM_IDLE, Texture, 0.1f);
	//Ani->SelectState(ANIM_IDLE);
	//m_uMapComponent[ID_ALL].insert({ L"Animation", Ani });

	return S_OK;
}

void CHp::Set_OrthoProj()
{
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);

	_matrix matTrans;
	D3DXMatrixScaling(&matView, 15.f, 15.f, 0.f);
	matTrans.Translation(-350.f, 250.f, 0.f);
	D3DXMatrixMultiply(&matView, &matView, &matTrans);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
}

CHp * CHp::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CHp* pInstance = new CHp(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

//void CHp::Create_HP(LPDIRECT3DDEVICE9 pGraphicDev)
//{
//	for (size_t i = 0; i < m_iMaxHp; i++)
//	{
//		CHp* pInstance = new CHp(pGraphicDev);
//		m_pHp.push_back(pInstance);
//	}
//}

void CHp::Free(void)
{
	__super::Free();

}
