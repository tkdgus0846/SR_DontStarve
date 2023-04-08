#include "Coin.h"
#include "Export_Function.h"



CCoin::CCoin(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUI(pGraphicDev)
{
}

CCoin::~CCoin()
{
}

HRESULT CCoin::Add_Component()
{
	// ����
	CRcTex* RcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(RcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", RcTex });

	CTexture* Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Coin_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"Coin_Texture", Texture });

	CAnimation* Ani = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(Ani, E_FAIL);

	Ani->BindAnimation(ANIM_IDLE, Texture, 0.15f);
	Ani->SelectState(ANIM_IDLE);
	m_uMapComponent[ID_ALL].insert({ L"Animation", Ani });


	// ����
	for (size_t i = 0; i < m_MaxNumber; i++)
	{
		CRcTex* RcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
		NULL_CHECK_RETURN(RcTex, E_FAIL);
		m_vecRc.push_back(RcTex);
	}

	m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Num_Texture", this));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);


	return S_OK;
}

HRESULT CCoin::Ready_GameObject(void)
{
	__super::Ready_GameObject();

	return S_OK;
}

_int CCoin::Update_GameObject(const _float & fTimeDelta)
{
	__super::Update_GameObject(fTimeDelta);

	return 0;
}

void CCoin::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CCoin::Render_GameObject(void)
{
	int strLen = pPlayerCoin.length();
	for (size_t i = 0, j = 2, k = 0; i < m_MaxNumber; i++, j--, k++)
	{
		_int iNum = 26;
		if (j >= strLen)
		{
			iNum = 26;
			k--;
		}
		else
		{
			iNum = m_iStartNum + pPlayerCoin[k] - 48;
		}
		Set_VeiwMatrix_UI(330 + (25.f * i), 250.f);
		m_pTextureCom->Render_Texture(iNum);
		m_vecRc[i]->Render_Component();
	}

	Set_VeiwMatrix_UI();

	__super::Render_GameObject();
}

void CCoin::Set_VeiwMatrix_UI()
{
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);

	_matrix matTrans;
	matTrans.Translation(300.f, 250.f, 0.f);
	D3DXMatrixScaling(&matView, 12.f, 12.f, 0.f);
	D3DXMatrixMultiply(&matView, &matView, &matTrans);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
}

void CCoin::Set_VeiwMatrix_UI(_float fX, _float fY)
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

_int CCoin::Compute_Num(string pPlayerCoin)
{/*
	int _tempCoin = stoi(pPlayerCoin[1]);
*/


	return _int();
}

CCoin * CCoin::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCoin* pInstance = new CCoin(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CCoin::Free(void)
{
	Safe_Release(m_pTextureCom);
	for_each(m_vecRc.begin(), m_vecRc.end(), CDeleteObj());
	__super::Free();
}
