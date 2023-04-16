#include "SpreaWeapon.h"
#include "Export_Function.h"
#include "BulletMgr.h"
#include "NormalBullet.h"


CSpreaWeapon::CSpreaWeapon(LPDIRECT3DDEVICE9 pGraphicDev)
	:CWeapon(pGraphicDev)
{
	Set_ObjTag(L"SpreadWeapon");

	this->m_fCycle = 0.1f;
	this->m_MaxBulletNum = 1000.f;
	this->m_CurBulletNum = 1000.f;
}

CSpreaWeapon::~CSpreaWeapon()
{
}


void CSpreaWeapon::Shot()
{
		if (CanShot())
		{
			for (size_t i = 0; i < 5; i++)
			{
				CBullet* bullet = Shot_Setting(i * 10.f - 20.f);

				if (bullet)
				{
					Add_GameObject(bullet);
					SpendBullet();
				}
			}
			m_bShooted = true;
			m_bEnableShot = false;
		}

}


CBullet * CSpreaWeapon::Shot_Setting(_float fAngle)
{
	CCamera* pCamera = dynamic_cast<CCamera*>(Engine::Get_Player()->Get_Component(L"Player_Camera", ID_UPDATE));
	if (pCamera == nullptr)	{return nullptr;}

	VIEWPARAMS* pCameraviewparams = pCamera->Get_Camera_ViewParams();

	_vec3 vAt = pCameraviewparams->vAt;
	_vec3 vEye = pCameraviewparams->vEye;

	_vec3 Look = vAt - vEye;

	D3DXVECTOR3 bulletDir;
	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationY(&rotationMatrix, D3DXToRadian(fAngle));
	D3DXVec3TransformNormal(&bulletDir, &Look, &rotationMatrix);

	D3DXVec3Normalize(&bulletDir, &bulletDir);
	

	CBullet* Bullet = CBulletMgr::GetInstance()->Pop(L"NormalBullet", m_pGraphicDev, m_pTransform->m_vInfo[INFO_POS], bulletDir, { 0.5f,0.5f,1.f }, false, 80.f);

	return Bullet;
}

_int CSpreaWeapon::Update_GameObject(const _float & fTimeDelta)
{
	cout << m_pTransform->m_vInfo[INFO_POS].x << endl;

	return __super::Update_GameObject(fTimeDelta);
}

HRESULT CSpreaWeapon::Add_Component()
{
	return S_OK;
}

HRESULT CSpreaWeapon::Ready_GameObject(void)
{
	return __super::Ready_GameObject();
}

void CSpreaWeapon::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CSpreaWeapon::Render_GameObject(void)
{
	__super::Render_GameObject();
}


CSpreaWeapon * CSpreaWeapon::Create(LPDIRECT3DDEVICE9 pGraphicDev, CTransform * pOnwerTransform)
{
	CSpreaWeapon* pInstance = new CSpreaWeapon(pGraphicDev);

	pInstance->m_pOwnerTransform = pOnwerTransform;

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		pInstance = nullptr;
	}

	return pInstance;
}

void CSpreaWeapon::Free(void)
{
	__super::Free();
}
