#include "Sonic.h"
#include "Export_Function.h"

CSonic::CSonic(LPDIRECT3DDEVICE9 pGraphicDev) :
	CGameObject(pGraphicDev)
{
	Set_LayerID(LAYER_PLAYER);
	Set_ObjTag(L"Sonic");

	m_pTransform->Set_MoveType(CTransform::MOVETYPE::AIRCRAFT);

	m_fTime = 0.f;
	m_fForce = 0.f;
}

CSonic::~CSonic()
{
}

_int CSonic::Update_GameObject(const _float & fTimeDelta)
{
	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);
	Add_RenderGroup(RENDER_ALPHA, this);

	Key_Input(fTimeDelta);

	Jump(fTimeDelta);
	
	return __super::Update_GameObject(fTimeDelta);
}

void CSonic::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CSonic::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_ViewMat);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_Projmat);

	__super::Render_GameObject();
}

void CSonic::Key_Input(const _float& fTimeDelta)
{
	if (Key_Down(DIK_SPACE))
	{
		m_pAnimation->SelectState(ANIM_RUN);

		m_fForce = 3.0f;
		m_fTime = 0.f;

		m_pTransform->Rot_Roll(9.f, 1.f);
	}
	
}

void CSonic::Jump(const _float& fTimeDelta)
{
	m_fTime += fTimeDelta;

	_float fY = m_fForce * m_fTime - 2.9f * m_fTime * m_fTime;

	if (fY < 0.f)
		m_pTransform->Rot_Roll(-70.f, fTimeDelta);
	m_pTransform->m_vInfo[INFO_POS].y += fY;
}

HRESULT CSonic::Add_Component()
{
	CRcTex* RcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(RcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", RcTex });

	CTexture* Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"SonicWalk_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"SonicWalk_Texture", Texture });

	m_pAnimation = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(m_pAnimation, E_FAIL);

	m_pAnimation->BindAnimation(ANIM_WALK, Texture, 0.08f);
	
	m_uMapComponent[ID_ALL].insert({ L"Animation", m_pAnimation });

	Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"SonicRun_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"SonicRun_Texture", Texture });

	m_pAnimation->BindAnimation(ANIM_RUN, Texture, 0.06);

	Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"SonicDead_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"SonicDead_Texture", Texture });

	m_pAnimation->BindAnimation(ANIM_DEAD, Texture);

	m_pAnimation->SelectState(ANIM_WALK);


	_vec3 eye = { 0.f,0.f,0.f }, at = { 0.f,0.f,1.f }, up = {0.f,1.f,0.f};
	m_ViewMat.LookAtLH(&eye, &at, &up);
	//m_ViewMat.Identity();
	//m_Projmat.PerspectiveFovLH();
	//m_Projmat.Identity();
	D3DXMatrixPerspectiveFovLH(&m_Projmat, D3DXToRadian(60.f), ((_float)WINCX / WINCY), 0.f, 1000.f);

	m_pTransform->Set_Pos({ -30.f,0.f,100.f });
	m_pTransform->Set_Scale({ 10.f,10.f,1.f });

	return S_OK;
}

CSonic * CSonic::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSonic*		pInstance = new CSonic(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}
