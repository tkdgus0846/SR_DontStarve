#include "stdafx.h"
#include "BossRoomCamera.h"

#include "Export_Function.h"

CBossRoomCamera::CBossRoomCamera(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
	Set_LayerID(LAYER_CAMERA);
	Set_ObjTag(L"BossRoomCamera");

}

CBossRoomCamera::~CBossRoomCamera()
{
}

HRESULT CBossRoomCamera::Ready_GameObject(void)
{
	HRESULT result = __super::Ready_GameObject();

	m_pTransform->m_vScale = { 1.f, 1.f, 1.f };
	m_pTransform->m_vInfo[INFO_POS] = _vec3(85.f, 10.f, 100.f);

	return result;
}

_int CBossRoomCamera::Update_GameObject(const _float & fTimeDelta)
{
	__super::Update_GameObject(fTimeDelta);

	return OBJ_NOEVENT;
}

void CBossRoomCamera::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CBossRoomCamera::Render_GameObject(void)
{
}

HRESULT CBossRoomCamera::Add_Component(void)
{
	m_pCamera = dynamic_cast<CCamera*>(Engine::Clone_Proto(L"Camera", this));
	NULL_CHECK_RETURN(m_pCamera, E_FAIL);
	m_uMapComponent[ID_UPDATE].emplace(L"Obj_Camera", m_pCamera);
	m_pCamera->Set_CameraName(L"Obj_Camera");

	return S_OK;
}

CBossRoomCamera * CBossRoomCamera::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBossRoomCamera* pInstance = new CBossRoomCamera(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CBossRoomCamera::Free()
{
	__super::Free();
}
