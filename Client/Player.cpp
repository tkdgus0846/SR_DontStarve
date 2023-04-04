#include "stdafx.h"
#include "Player.h"

#include "Export_Function.h"
#include "BulletMgr.h"
#include "NormalBullet.h"

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev), m_fSpeed(0.f)
	, m_bFix(false)
{
	
}

CPlayer::~CPlayer()
{
}

HRESULT CPlayer::Ready_GameObject(void)
{
	HRESULT result = __super::Ready_GameObject();

	m_pTransform->m_vScale = { 1.f, 1.f, 1.f };
	m_pTransform->m_vInfo[INFO_POS] = _vec3(10.f, -5.f, 30.f);

	m_fSpeed = 10.f;

	return result;
}
_int CPlayer::Update_GameObject(const _float& fTimeDelta)
{
	Key_Input(fTimeDelta);

	// m_planeVec

	if (m_bFix)
	{
		Fix_Mouse();
		Mouse_Move(fTimeDelta);
	}

	__super::Update_GameObject(fTimeDelta);


	Engine::Add_RenderGroup(RENDER_ALPHA, this);
	return OBJ_NOEVENT;
}
void CPlayer::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
	
	// 충돌 처리 부분.
}

void CPlayer::Render_GameObject(void)
{
	__super::Render_GameObject();

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

	__super::Render_GameObject();

	//m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	//m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	
}

void CPlayer::OnTriggerStay(const CCollider * other)
{
	static int i = 0;
	//cout << "충돌 테스트 플레이어" << ++i <<endl;
}

HRESULT CPlayer::Add_Component(void)
{
	CComponent*		pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex",this));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_uMapComponent[ID_DYNAMIC].insert({ L"RcTex", pComponent });
		
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

	if (Engine::Key_Pressing(DIK_W))	m_pTransform->Move_Walk(m_fSpeed, fTimeDelta);
	if (Engine::Key_Pressing(DIK_S))	m_pTransform->Move_Walk(-m_fSpeed, fTimeDelta);
	if (Engine::Key_Pressing(DIK_A))	m_pTransform->Move_Strafe(-m_fSpeed, fTimeDelta);
	if (Engine::Key_Pressing(DIK_D))	m_pTransform->Move_Strafe(m_fSpeed, fTimeDelta);
	if (Engine::Key_Pressing(DIK_Q))	m_pTransform->Move_Fly(m_fSpeed, fTimeDelta);
	if (Engine::Key_Pressing(DIK_E))	m_pTransform->Move_Fly(-m_fSpeed, fTimeDelta);

	if (Engine::Key_Down((DIK_F1))) 	Engine::On_Camera(L"Player_Camera");
	if (Engine::Key_Pressing(DIK_LCONTROL) && Engine::Key_Down(DIK_1)) m_bFix = !m_bFix;

	static float ShootCoolTime = 0.f;
	ShootCoolTime += fTimeDelta;
	if (ShootCoolTime > 0.2f)
	{
		if (Engine::Get_DIMouseState(DIM_LB))
		{
			CNormalBullet* bullet = CBulletMgr::GetInstance()->Pop<CNormalBullet>(L"NormalBullet", m_pGraphicDev, m_pTransform->m_vInfo[INFO_POS], vDir, false);
			Add_GameObject(LAYER_BULLET, L"Bullet", bullet);
			ShootCoolTime = 0.f;
		}
	}
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