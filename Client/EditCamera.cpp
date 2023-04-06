#include "EditCamera.h"

#include "Export_Function.h"

CEditCamera::CEditCamera(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev), m_fSpeed(0.f), m_bFix(true)
{
}

CEditCamera::~CEditCamera()
{
}

HRESULT CEditCamera::Ready_GameObject(void)
{
	HRESULT result = __super::Ready_GameObject();

	m_pTransform->m_vScale = { 1.f, 1.f, 1.f };
	m_pTransform->m_vInfo[INFO_POS] = _vec3(15.f, 20.f, 30.f);
	m_pTransform->Set_MoveType(CTransform::AIRCRAFT);

	m_fSpeed = 40.f;

	return result;
}

_int CEditCamera::Update_GameObject(const _float & fTimeDelta)
{
	Key_Input(fTimeDelta);

	if (m_bFix)
	{
		Fix_Mouse();
		Mouse_Move(fTimeDelta);
	}

	__super::Update_GameObject(fTimeDelta);

	return OBJ_NOEVENT;
}

void CEditCamera::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CEditCamera::Render_GameObject(void)
{
}

HRESULT CEditCamera::Add_Component()
{
	CComponent*		pComponent = nullptr;

	pComponent = m_pCamera = dynamic_cast<CCamera*>(Engine::Clone_Proto(L"Camera", this));
	NULL_CHECK_RETURN(m_pCamera, E_FAIL);
	m_uMapComponent[ID_UPDATE].insert({ L"Edit_Camera", pComponent });
	m_pCamera->Set_CameraName(L"Edit_Camera");

	return S_OK;
}

void CEditCamera::Key_Input(const _float & fTimeDelta)
{
	if (Engine::Key_Pressing(DIK_W))	m_pTransform->Move_Walk(m_fSpeed, fTimeDelta);
	if (Engine::Key_Pressing(DIK_S))	m_pTransform->Move_Walk(-m_fSpeed, fTimeDelta);
	if (Engine::Key_Pressing(DIK_A))	m_pTransform->Move_Strafe(-m_fSpeed, fTimeDelta);
	if (Engine::Key_Pressing(DIK_D))	m_pTransform->Move_Strafe(m_fSpeed, fTimeDelta);
	if (Engine::Key_Pressing(DIK_Q))	m_pTransform->Move_Fly(m_fSpeed, fTimeDelta);
	if (Engine::Key_Pressing(DIK_E))	m_pTransform->Move_Fly(-m_fSpeed, fTimeDelta);

	if (Engine::Key_Down(DIK_1)) m_bFix = !m_bFix;

	if (Engine::Get_DIMouseState(DIM_LB))
	{

	}
}

void CEditCamera::Mouse_Move(const _float & fTimeDelta)
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

void CEditCamera::Fix_Mouse()
{
	POINT ptMouse{ WINCX >> 1, WINCY >> 1 };

	ClientToScreen(g_hWnd, &ptMouse);
	SetCursorPos(ptMouse.x, ptMouse.y);
}

/*
Ray PickingRay(POINT pt);
1. ī�޶� ��ġ���� ���콺�� ������ ��.
-> ����Ʈ to ����
-> ���� to �� �����̽�
-> �� �����̽� to ����
-> ray��ü ��ȯ.


_bool IntersectRayTri(Ray ray, CVIBuffer _pVB, OUT float& distance, OUT _vec3& _InterPos)
2. ���� room�ȿ� �ִ� ��� ��ü���� ���ؽ� ���ۿ� ������ �����ϴ��� �˻��Ѵ�.
-> VIBuffer������Ʈ�� �Ű� ������ ���ڷ� �޴´�.
-> ������ VIBuffer�� �ﰢ������ �����ϴ��� �˻��Ѵ�.*/

CEditCamera * CEditCamera::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CEditCamera*		pInstance = new CEditCamera(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CEditCamera::Free()
{
	__super::Free();
}
