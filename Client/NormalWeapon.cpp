#include "NormalWeapon.h"
#include "Export_Function.h"

#include "BulletMgr.h"
#include "NormalBullet.h"

CNormalWeapon::CNormalWeapon(LPDIRECT3DDEVICE9 pGraphicDev) :
	CWeapon(pGraphicDev)
{
}

CNormalWeapon::~CNormalWeapon()
{
}

void CNormalWeapon::Shot()
{
	if (CanShot())
	{
		CCamera* playerCamera = dynamic_cast<CCamera*>(Get_Player()->Get_Component(L"Player_Camera", ID_UPDATE));

		if (playerCamera == nullptr) return;

		

		
		_matrix cameraRotationMat, myTransMat;
		m_pGraphicDev->GetTransform(D3DTS_VIEW, &cameraRotationMat);
		cameraRotationMat.Inverse();
		cameraRotationMat._41 = 0.f;
		cameraRotationMat._42 = 0.f;
		cameraRotationMat._43 = 0.f;

		myTransMat.Translation(m_pOwnerTransform->m_vInfo[INFO_POS].x, m_pOwnerTransform->m_vInfo[INFO_POS].y, m_pOwnerTransform->m_vInfo[INFO_POS].z);

		_matrix mat = cameraRotationMat * myTransMat;

		_vec3 bulletPos = { +1.0f,-1.5f,0.f };
		bulletPos.TransformCoord(&mat);


		VIEWPARAMS* cameraViewparams = playerCamera->Get_Camera_ViewParams();
		_vec3& cameraAt = cameraViewparams->vAt;

		

		_vec3 bulletDir = cameraAt - bulletPos;
		bulletDir.Normalize();

		/*bulletDir = cameraAt - cameraViewparams->vEye;
		bulletDir.Normalize();*/

		cout << bulletDir.x << " " << bulletDir.y << " " << bulletDir.z << " \n" << endl;

		CBullet* bullet = CBulletMgr::GetInstance()->Pop<CNormalBullet>(L"NormalBullet", m_pGraphicDev, bulletPos, bulletDir, false);
		Add_GameObject(LAYER_BULLET, L"NormalBullet", bullet);
	}
}

_int CNormalWeapon::Update_GameObject(const _float& fTimeDelta)
{
	return __super::Update_GameObject(fTimeDelta);
}

HRESULT CNormalWeapon::Add_Component()
{

	/*CRcTex* rcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(rcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", rcTex });*/
	return S_OK;
}

HRESULT CNormalWeapon::Ready_GameObject(void)
{
	return __super::Ready_GameObject();
}

void CNormalWeapon::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CNormalWeapon::Render_GameObject(void)
{
	
	__super::Render_GameObject();
}

CNormalWeapon* CNormalWeapon::Create(LPDIRECT3DDEVICE9 pGraphicDev, CTransform* pOnwerTransform)
{
	CNormalWeapon*		pInstance = new CNormalWeapon(pGraphicDev);
	pInstance->m_pOwnerTransform = pOnwerTransform;

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CNormalWeapon::Free(void)
{
	__super::Free();
}
