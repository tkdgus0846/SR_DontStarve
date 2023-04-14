#include "stdafx.h"
#include "Player.h"

#include "Export_Function.h"
#include "BulletMgr.h"
#include "NormalBullet.h"
#include "NormalWeapon.h"
#include "IceBeamWeapon.h"
#include "FlameProjector.h"

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	: CCreature(pGraphicDev)
	, m_bFix(true)
	, m_eCurWeaponType(WEAPONEND)
	, m_pCurWeapon(nullptr)
{
	Set_LayerID(LAYER_PLAYER);
	Set_ObjTag(L"Player");

	
}

CPlayer::~CPlayer()
{
}

HRESULT CPlayer::Ready_GameObject(void)
{
	HRESULT result = __super::Ready_GameObject();

	Engine::On_Camera(L"Player_Camera");

	m_pTransform->m_vScale = { 1.f, 1.f, 1.f };
	m_pTransform->m_vInfo[INFO_POS] = {4.f,4.f,4.f};
	m_pTransform->m_vInfo[INFO_LOOK] = { 0.f, 0.f, 1.f };

	m_fSpeed = 12.f;
	m_iHp = 20;

	Set_Player(this);

	for (int i = 0; i < WEAPONEND; i++)
		m_MyWeaponList[i] = nullptr;

	m_MyWeaponList[BIGSHOT] = CNormalWeapon::Create(m_pGraphicDev, m_pTransform);
	m_MyWeaponList[FREEZESHOT] = CIceBeamWeapon::Create(m_pGraphicDev, m_pTransform);
	//m_MyWeaponList[FLAMESHOT] = CFlameProjector::Create(m_pGraphicDev, m_pTransform);

	Change_Weapon(BIGSHOT);

	return result;
}
_int CPlayer::Update_GameObject(const _float& fTimeDelta)
{
	if (GetDead()) return OBJ_DEAD;

	/*cout << m_pTransform->m_vInfo[INFO_POS].x << " " << m_pTransform->m_vInfo[INFO_POS].y << " " << m_pTransform->m_vInfo[INFO_POS].z << endl;*/

	cout << m_fUltimateGuage << endl;
	Key_Input(fTimeDelta);

	// m_planeVec
	if (m_bFix)
	{
		Fix_Mouse();
		Mouse_Move(fTimeDelta);
	}

	__super::Update_GameObject(fTimeDelta);

	m_pCurWeapon->Update_GameObject(fTimeDelta);

	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);
	return OBJ_NOEVENT;
}
void CPlayer::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
	m_pCurWeapon->LateUpdate_GameObject();
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

	__super::Render_GameObject();
	/*m_pCurWeapon->Render_GameObject();*/

	//m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	//m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
}

void CPlayer::OnCollisionEnter(const Collision * collsion)
{
}

void CPlayer::OnCollisionStay(const Collision * collision)
{
	__super::OnCollisionStay(collision);
}

void CPlayer::OnCollisionExit(const Collision * collision)
{
}

void CPlayer::Change_Weapon(WEAPONTYPE eWeaponType)
{
	if (eWeaponType == m_eCurWeaponType) return;

	m_pCurWeapon = m_MyWeaponList[eWeaponType];

	if (m_pCurWeapon == nullptr)
	{
		m_pCurWeapon = m_MyWeaponList[m_eCurWeaponType];
		return;
	}
		
	m_eCurWeaponType = eWeaponType;
}

void CPlayer::Next_Weapon()
{
	_int eWeaponType = m_eCurWeaponType + 1;
	if (eWeaponType >= WEAPONEND)
		eWeaponType = 0;

	if (m_MyWeaponList[eWeaponType] == nullptr)
	{
		for (;; eWeaponType++)
		{
			if (eWeaponType >= WEAPONEND)
				eWeaponType = 0;

			if (m_MyWeaponList[eWeaponType] != nullptr) break;
		}
	}

	Change_Weapon((WEAPONTYPE)eWeaponType);
}

void CPlayer::Prev_Weapon()
{
	_int eWeaponType = m_eCurWeaponType - 1;
	if (eWeaponType < 0)
		eWeaponType = WEAPONEND - 1;

	if (m_MyWeaponList[eWeaponType] == nullptr)
	{
		for (; ; eWeaponType--)
		{
			if (eWeaponType < 0)
				eWeaponType = WEAPONEND - 1;

			if (m_MyWeaponList[eWeaponType] != nullptr) break;
		}
	}

	Change_Weapon((WEAPONTYPE)eWeaponType);
}

void CPlayer::Gain_Weapon(WEAPONTYPE eWeaponType)
{
	
	if (m_MyWeaponList[eWeaponType] == nullptr)
	{
		CWeapon* gainWeapon = nullptr;
		switch (eWeaponType)
		{
		case BIGSHOT:
			gainWeapon = CNormalWeapon::Create(m_pGraphicDev, m_pTransform);
			break;
		case EXPLOSIVESHOT:
			break;
		case FLAMESHOT:
			gainWeapon = CFlameProjector::Create(m_pGraphicDev, m_pTransform);
			break;
		case RAPIDSHOT:
			break;
		case SPREADSHOT:
			break;
		case FREEZESHOT:
			gainWeapon = CIceBeamWeapon::Create(m_pGraphicDev, m_pTransform);
			break;
		case LASERSHOT:
			break;
		default:
			break;
		}
		m_MyWeaponList[eWeaponType] = gainWeapon;
	}
	else
	{
		m_MyWeaponList[eWeaponType]->GainBullet(10);
	}
}

HRESULT CPlayer::Add_Component(void)
{
	/*CRcTex* pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex",this));
	NULL_CHECK_RETURN(pBufferCom, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", pBufferCom });*/
		
	/*CTexture* pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Player_Texture",this));
	NULL_CHECK_RETURN(pTextureCom, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"Player_Texture", pTextureCom });
	pTextureCom->Set_Texture_Num(0);*/

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_PLAYER));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"BodyCollider", pCollider });
	pCollider->Set_BoundingBox({2.f,7.f,2.f});

	/*pComponent = m_pRigid = dynamic_cast<CRigidbody*>(Engine::Clone_Proto(L"Rigidbody", this));
	NULL_CHECK_RETURN(m_pRigid, E_FAIL);
	m_uMapComponent[ID_DYNAMIC].insert({ L"Player_Rigidbody", pComponent });*/

	CCamera* m_pCamera = dynamic_cast<CCamera*>(Engine::Clone_Proto(L"Camera", this));
	NULL_CHECK_RETURN(m_pCamera, E_FAIL);
	m_uMapComponent[ID_UPDATE].insert({ L"Player_Camera", m_pCamera });
	m_pCamera->Set_CameraName(L"Player_Camera");
	m_pCamera->Set_ProjParams(PROJPARAMS(
		D3DXToRadian(60.f),
		(_float)WINCX / WINCY,
		0.1f, 70.f));

	CRigidbody* pRigidBody = dynamic_cast<CRigidbody*>(Engine::Clone_Proto(L"RigidBody", this));
	NULL_CHECK_RETURN(pRigidBody, E_FAIL);
	m_uMapComponent[ID_UPDATE].insert({ L"RigidBody", pRigidBody });

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
	for (auto it : m_MyWeaponList)
		Safe_Release(it);
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
	if (Engine::Key_Down(DIK_Q))	Prev_Weapon();
	if (Engine::Key_Down(DIK_E))	Next_Weapon();
	if (Engine::Key_Down(DIK_P))	Get_Damaged(1);

	if (Engine::Key_Down((DIK_F1))) 	Engine::On_Camera(L"Player_Camera");
	if (Engine::Key_Down(DIK_1)) m_bFix = !m_bFix;
	if (Engine::Key_Down((DIK_C))) Engine::Toggle_ColliderRender();

	if (Engine::Get_DIMouseState(DIM_LB))
	{
		D3DXVECTOR3 screenCenter = { WINCX / 2.f, WINCY / 2.f, 0.f };
		D3DXVECTOR3 bulletPosition(1.0f, 1.0f, 1.0f);

		bulletPosition = m_pTransform->m_vInfo[INFO_POS] + bulletPosition;
		m_pCurWeapon->Shot();
		/*D3DXVECTOR3 centerWorld;
		D3DXMATRIX viewMatrix, projMatrix;
		m_pGraphicDev->GetTransform(D3DTS_VIEW, &viewMatrix);
		m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &projMatrix);
		m_pGraphicDev->GetViewport()
		D3DXVec3Unproject(&centerWorld, &screenCenter, &pViewport, &projMatrix, &viewMatrix, m_pTransform->Get_WorldMatrixPointer());*/
	}

	if (Engine::Key_Down(DIK_F))
	{
		CBullet* bullet = CBulletMgr::GetInstance()->Pop(L"VortexBullet", m_pGraphicDev, m_pTransform->m_vInfo[INFO_POS] + m_pTransform->m_vInfo[INFO_LOOK] * 1.3f, m_pTransform->m_vInfo[INFO_LOOK], { 1.f,1.f,1.f });
		Add_GameObject(bullet);
	}
}

void CPlayer::Mouse_Move(const _float& fTimeDelta)
{
	_long dwMouseMove = 0;

	if (dwMouseMove = Engine::Get_DIMouseMove(DIMS_Y))
	{
		m_pTransform->m_vInfo[INFO_LOOK] += _vec3(0.f, 1.f, 0.f) * _float(-dwMouseMove) * fTimeDelta / 10.f;
	}

	if (dwMouseMove = Engine::Get_DIMouseMove(DIMS_X))
	{
		m_pTransform->Rot_Yaw(_float(dwMouseMove) * 5.f, fTimeDelta);
	}
}

void CPlayer::Fix_Mouse()
{
	POINT ptMouse{ WINCX >> 1, WINCY >> 1 };

	ClientToScreen(g_hWnd, &ptMouse);
	SetCursorPos(ptMouse.x, ptMouse.y);
}