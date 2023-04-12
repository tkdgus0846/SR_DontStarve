#include "Pyramid.h"
#include "Export_Function.h"

CPyramid::CPyramid(LPDIRECT3DDEVICE9 pGraphicDev) :
	CMapObj(pGraphicDev)
{
	Set_ObjTag(L"Pyramid");
}

CPyramid::~CPyramid()
{
}

HRESULT CPyramid::Ready_GameObject(void)
{
	HRESULT result = __super::Ready_GameObject();
	return result;
}

_int CPyramid::Update_GameObject(const _float & fTimeDelta)
{
	if (GetDead()) 
		return OBJ_DEAD;
	__super::Update_GameObject(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_NONALPHA, this);


	return OBJ_NOEVENT;
}

void CPyramid::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CPyramid::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());

	__super::Render_GameObject();
}

void CPyramid::OnCollisionEnter(const Collision * collsion)
{
}

void CPyramid::OnCollisionStay(const Collision * collision)
{
}

void CPyramid::OnCollisionExit(const Collision * collision)
{
}

HRESULT CPyramid::Add_Component()
{
	CComponent *pComponent;

	pComponent = dynamic_cast<CFrustrumNormalTex*>(Engine::Clone_Proto(L"FrustrumNormalTex", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FrustrumNormalTex", pComponent });

	pComponent = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"SkyBox_Texture", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"SkyBox_Texture", pComponent });

	return S_OK;
}

CPyramid * CPyramid::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPyramid* pInstance = new CPyramid(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CPyramid::Free(void)
{
	__super::Free();
}
