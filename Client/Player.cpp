#include "stdafx.h"
#include "Player.h"

#include "Export_Function.h"

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
	
}

CPlayer::~CPlayer()
{
}

HRESULT CPlayer::Ready_GameObject(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransform->m_vScale = { 1.f, 1.f, 1.f };
	m_pTransform->m_vInfo[INFO_POS] = _vec3(10.f, -5.f, 30.f);

	return S_OK;
}
_int CPlayer::Update_GameObject(const _float& fTimeDelta)
{
	Key_Input(fTimeDelta);

	// m_planeVec


	//Fix_Mouse();
	Mouse_Move(fTimeDelta);

	__super::Update_GameObject(fTimeDelta);


	Engine::Add_RenderGroup(RENDER_ALPHA, this);
	return 0;
}
void CPlayer::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
	
	// 충돌 처리 부분.
}

void CPlayer::Render_GameObject(void)
{
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	/*m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAREF, 0xc0);*/

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());

	m_pTextureCom->Set_Texture(0);

	m_pBufferCom->Render_Buffer();

	//m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	//m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	__super::Render_GameObject();
}

void CPlayer::OnTriggerStay(const CCollider * other)
{
	static int i = 0;
	cout << "충돌 테스트 플레이어" << ++i <<endl;
}

HRESULT CPlayer::Add_Component(void)
{
	CComponent*		pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex",this));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"RcTex", pComponent });
		
	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Player_Texture",this));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"Player_Texture", pComponent });

	pComponent = m_pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", this));
	NULL_CHECK_RETURN(m_pCollider, E_FAIL);
	m_uMapComponent[ID_DYNAMIC].insert({ L"Player_Collider", pComponent });
	m_pCollider->Set_BoundingBox({3.f,3.f,3.f});

	/*pComponent = m_pRigid = dynamic_cast<CRigidbody*>(Engine::Clone_Proto(L"Rigidbody", this));
	NULL_CHECK_RETURN(m_pRigid, E_FAIL);
	m_uMapComponent[ID_DYNAMIC].insert({ L"Player_Rigidbody", pComponent });*/

	pComponent = m_pCamera = dynamic_cast<CCamera*>(Engine::Clone_Proto(L"Camera", this));
	NULL_CHECK_RETURN(m_pCamera, E_FAIL);

	m_uMapComponent[ID_DYNAMIC].insert({ L"Player_Camera", pComponent });
	m_pCamera->Set_CameraName(L"Player_Camera");


	return S_OK;
}



CPlayer* CPlayer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPlayer*		pInstance = new CPlayer(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CPlayer::Free(void)
{
	__super::Free();
}

void CPlayer::Key_Input(const _float & fTimeDelta)
{
	_vec3		vDir;
	_vec3		vRight;
	m_pTransform->Get_Info(INFO_LOOK, &vDir);
	m_pTransform->Get_Info(INFO_RIGHT, &vRight);

	if (GetAsyncKeyState('W'))	m_pTransform->Move_Walk(m_fSpeed, fTimeDelta);
	if (GetAsyncKeyState('S'))	m_pTransform->Move_Walk(-m_fSpeed, fTimeDelta);
	if (GetAsyncKeyState('A'))	m_pTransform->Move_Strafe(-m_fSpeed, fTimeDelta);
	if (GetAsyncKeyState('D'))	m_pTransform->Move_Strafe(m_fSpeed, fTimeDelta);

	if (GetAsyncKeyState('Q'))	m_pTransform->Move_Fly(m_fSpeed, fTimeDelta);
	if (GetAsyncKeyState('E'))	m_pTransform->Move_Fly(-m_fSpeed, fTimeDelta);
	

	if (GetAsyncKeyState(VK_F1)) Engine::On_Camera(L"Player_Camera");
}


void CPlayer::Mouse_Move(const _float& fTimeDelta)
{
	_long dwMouseMove = 0;

	if (dwMouseMove = Engine::Get_DIMouseMove(DIMS_Y))
	{
		m_pTransform->m_vInfo[INFO_LOOK] += _vec3(0.f, 1.f, 0.f) * -dwMouseMove * fTimeDelta / 10.f;
	}

	if (dwMouseMove = Engine::Get_DIMouseMove(DIMS_X))
	{
		m_pTransform->Rot_Yaw(dwMouseMove * 5.f, fTimeDelta);
	}
}

void CPlayer::Fix_Mouse()
{
	POINT ptMouse{ WINCX >> 1, WINCY >> 1 };

	ClientToScreen(g_hWnd, &ptMouse);
	SetCursorPos(ptMouse.x, ptMouse.y);
}