#include "stdafx.h"
#include "CutSceneCamera.h"

#include "RoomMgr.h"
#include "Export_Function.h"

CCutSceneCamera::CCutSceneCamera(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev), m_fDegree(0.f), m_bIsDone(false)
{
	Set_LayerID(LAYER_CAMERA);
	Set_ObjTag(L"CutScene_Camera");
}

CCutSceneCamera::~CCutSceneCamera()
{
}

HRESULT CCutSceneCamera::Ready_GameObject(void)
{
	HRESULT result = __super::Ready_GameObject();

	m_fDegree = 60.f;
	m_pTransform->m_vScale = { 1.f, 1.f, 1.f };
	m_pTransform->m_vInfo[INFO_POS] = _vec3(85.f, 5.f, 100.f);

	return result;
}

_int CCutSceneCamera::Update_GameObject(const _float & fTimeDelta)
{
	if (Get_WorldTime() < 10.f)
		m_bIsDone = false;

	if (ROOM_MGR->Get_CurRoom()->Get_Room_Index() == 4)
		CutScene();
	else
		On_Camera(L"Player_Camera");

	__super::Update_GameObject(fTimeDelta);

	return OBJ_NOEVENT;
}

void CCutSceneCamera::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CCutSceneCamera::Render_GameObject(void)
{
}

HRESULT CCutSceneCamera::Add_Component(void)
{
	m_pCamera = dynamic_cast<CCamera*>(Engine::Clone_Proto(L"Camera", this));
	NULL_CHECK_RETURN(m_pCamera, E_FAIL);
	m_uMapComponent[ID_UPDATE].emplace(L"CutScene_Camera", m_pCamera);
	m_pCamera->Set_CameraName(L"CutScene_Camera");

	return S_OK;
}

void CCutSceneCamera::CutScene()
{
	static _float fTime = 0.f;
	if (m_bIsDone)
		return;

	_float fps60 = Get_Timer(L"Timer_FPS60");
	fTime += fps60;

	if (fTime > 3.f)
	{
		m_bIsDone = true;

		if (CRenderer::GetInstance()->GetIsRenderUI() == false)
			CRenderer::GetInstance()->ToggleRenderUI();

		Engine::Reset_SlowTime(fps60);
		On_Camera(L"Player_Camera");
		return;
	}

	if (CRenderer::GetInstance()->GetIsRenderUI() == true)
		CRenderer::GetInstance()->ToggleRenderUI();

	Engine::Stop_SlowTime();

	On_Camera(L"CutScene_Camera");

	CGameObject* pBoss = Get_Layer(LAYER_BOSS)->Get_GameObject(L"NubBoss");
	if (pBoss == nullptr)
		return;

	m_pTransform->m_vInfo[INFO_LOOK] = pBoss->m_pTransform->m_vInfo[INFO_POS] - m_pTransform->m_vInfo[INFO_POS];

	if (m_fDegree < 30.f)
		m_fDegree = 30.f;

	m_pCamera->Set_FOV(m_fDegree);
	m_fDegree -= 0.5f;
}

CCutSceneCamera * CCutSceneCamera::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCutSceneCamera* pInstance = new CCutSceneCamera(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CCutSceneCamera::Free()
{
	__super::Free();
}
