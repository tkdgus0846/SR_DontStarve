#include "stdafx.h"
#include "SkyBox.h"

#include "Export_Function.h"

CSkyBox::CSkyBox(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
}

CSkyBox::~CSkyBox()
{
}

HRESULT CSkyBox::Ready_GameObject(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransform->m_vScale = { 40.f, 40.f, 40.f };


	return S_OK;
}
_int CSkyBox::Update_GameObject(const _float& fTimeDelta)
{
	_matrix		matCamWorld;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matCamWorld);
	D3DXMatrixInverse(&matCamWorld, 0, &matCamWorld);

	m_pTransform->Set_Pos(matCamWorld._41, matCamWorld._42 + 3.f, matCamWorld._43);
	
	__super::Update_GameObject(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_PRIORITY, this);

	return 0;
}
void CSkyBox::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

// D3DRS_ZENABLE			: Z���ۿ� Z���� ������ ����� �ϵ� ������ �������� ���� �����ϴ� �ɼ�
// D3DRS_ZWRITEENABLE		: Z���ۿ� �ȼ��� ���� ���� ����� ���� ���� �����ϴ� �ɼ�

void CSkyBox::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	m_pTextureCom->Set_Texture(3);

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

HRESULT CSkyBox::Add_Component(void)
{
	CComponent*		pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CCubeTex*>(Engine::Clone_Proto(L"CubeTex",this));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"CubeTex", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"SkyBox_Texture",this));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"SkyBox_Texture", pComponent });

	return S_OK;
}



CSkyBox* CSkyBox::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSkyBox*		pInstance = new CSkyBox(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CSkyBox::Free(void)
{
	__super::Free();
}

