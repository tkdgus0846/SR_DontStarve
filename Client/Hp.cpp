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
	if (Engine::Key_Down(DIK_2))
	{
		pPlayerHp -= 1;
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
	_int PlayerHp = pPlayerHp; // �÷��̾� ü��
	for (size_t i = 0; i < m_iMaxHp; i++)
	{
		m_iCurrentHp = Compute_Hp(PlayerHp);
		Set_VeiwMatrix_UI(-350 + (50.f * i) , 250.f);
		m_pTextureCom->Render_Texture(m_iCurrentHp);
		m_vecRc[i]->Render_Component();
	}
}

HRESULT CHp::Add_Component(void)
{
	for (_int i = 0; i < m_iMaxHp; i++)
	{
		CRcTex* RcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
		NULL_CHECK_RETURN(RcTex, E_FAIL);

		m_vecRc.push_back(RcTex);
	}


	m_pTextureCom = nullptr;
	m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Hp_Texture", this));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);

	return S_OK;
}

void CHp::Set_VeiwMatrix_UI(_float fX, _float fY)
{
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);

	_matrix matTrans;
	D3DXMatrixScaling(&matView, 22.f, 20.f, 0.f);
	matTrans.Translation(fX, fY, 0.f);
	D3DXMatrixMultiply(&matView, &matView, &matTrans);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
}

_int CHp::Compute_Hp(_int& pPlayerHp)
{
	if (pPlayerHp - 4 >= 0)
	{
		m_iCurrentHp = 0;
		pPlayerHp = pPlayerHp - 4;
		return m_iCurrentHp;
	}
	else
	{
		if (pPlayerHp <= 0)
		{
			m_iCurrentHp = 4;
		}
		else
		{
			pPlayerHp = pPlayerHp - 4;
			m_iCurrentHp = -(pPlayerHp);
		}
	}
	return m_iCurrentHp;
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
	Safe_Release(m_pTextureCom);
	for_each(m_vecRc.begin(), m_vecRc.end(), CDeleteObj());
	__super::Free();
}