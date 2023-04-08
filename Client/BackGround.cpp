#include "stdafx.h"
#include "BackGround.h"

#include "Export_Function.h"

CBackGround::CBackGround(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
}

CBackGround::~CBackGround()
{
}

HRESULT CBackGround::Ready_GameObject(void)
{
	HRESULT result = __super::Ready_GameObject();

	return result;
}

_int CBackGround::Update_GameObject(const _float& fTimeDelta)
{
	__super::Update_GameObject(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA_UI, this);

	return 0;
}

void CBackGround::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CBackGround::Render_GameObject(void)
{
	static _float posX = 0.f;
	static _float posY = 0.f;
	static _float incX = 1.9f;
	static _float angle = 0.f;


	/*if (posX >= 190.f)
	incX *= -1.f;

	if (posX < 150.f)
	incX *= -1.f;

	posX += incX;*/
	_matrix viewMatrix, transMatrix, scaleMatrix, rotationMatrix;
	transMatrix.Translation(posX, posY, 0.f);
	scaleMatrix.Scaling(200.f, 112.f, 0.f);
	rotationMatrix.RotationZ(D3DXToRadian(angle));
	viewMatrix.Identity();

	viewMatrix = viewMatrix * scaleMatrix * rotationMatrix * transMatrix;

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &viewMatrix);
	__super::Render_GameObject();
}

HRESULT CBackGround::Add_Component(void)
{
	CComponent*		pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex",this));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", pComponent });


	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Logo_Texture",this));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"Logo_Texture", pComponent });

	return S_OK;
}

CBackGround* CBackGround::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBackGround*		pInstance = new CBackGround(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CBackGround::Free(void)
{
	__super::Free();
}
