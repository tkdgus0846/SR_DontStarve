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

	m_fSpeed = 20.f;

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

_bool CEditCamera::Compute_RayCastHitBuffer(IN Ray * pRay, IN CVIBuffer * pVIBuffer, OUT Triangle & tri)
{
	_bool success = false;
	_float u, v;
	_float dist = FLT_MAX;
	_float distTemp = 0.f;
	VTXTEX* vertices = nullptr;
	INDEX32* indices = nullptr;
	_bool tempSuccess;

	D3DVERTEXBUFFER_DESC vbDescription;
	D3DINDEXBUFFER_DESC inDescription;

	pVIBuffer->GetVertexBuffer()->GetDesc(&vbDescription);
	pVIBuffer->GetIndexBuffer()->GetDesc(&inDescription);


	pVIBuffer->GetVertexBuffer()->Lock(0, 0, (void**)vertices, 0);
	pVIBuffer->GetIndexBuffer()->Lock(0, 0, (void**)indices, 0);
	
	_vec3 v0;

	_ulong dwSize = inDescription.Size;
	for (_ulong i = 0; i < dwSize; ++i)
	{
		


		//v0 = vertices[indices[i]._0];
		//tri.v[1] = 
		//tri.v[2] = 


		//tri.v[0] = vFloorArr[dwIndex + VTXCNTX];
		//tri.v[1] = vFloorArr[dwIndex + VTXCNTX + 1];
		//tri.v[2] = vFloorArr[dwIndex + 1];
	}

	pVIBuffer->GetVertexBuffer()->Unlock();
	pVIBuffer->GetIndexBuffer()->Unlock();

	return _bool();
}

_bool CEditCamera::Compute_RayCastHitFloor(_vec3 * result, const Ray* pRay)
{
	_bool success = false;
	_float u, v;
	_float dist = FLT_MAX;
	_float distTemp = 0.f;

	_vec3 vFloorArr[VTXCNTX * VTXCNTZ];
	_ulong	dwIndex = 0;

	for (_ulong i = 0; i < VTXCNTZ; ++i)
	{
		for (_ulong j = 0; j < VTXCNTX; ++j)
		{
			dwIndex = i * VTXCNTX + j;

			vFloorArr[dwIndex] = {
				_float(j * VTXITV),
				0.f,
				_float(i * VTXITV) };
		}
	}

	_vec3 v0, v1, v2;

	for (int i = 0; i < VTXCNTZ - 1; i++)
	{
		for (int j = 0; j < VTXCNTX - 1; j++)
		{
			DWORD dwIndex = i * VTXCNTX + j;
			_bool tempSuccess;

			v0 = vFloorArr[dwIndex + VTXCNTX];
			v1 = vFloorArr[dwIndex + VTXCNTX + 1];
			v2 = vFloorArr[dwIndex + 1];

			tempSuccess = D3DXIntersectTri(&v0, &v1, &v2
				, (const D3DXVECTOR3*)(&pRay->vOrigin)
				, (const D3DXVECTOR3*)(&pRay->vDirection)
				, &u, &v, &distTemp);

			if (tempSuccess && (dist > distTemp))
			{
				*result = v0 + u*(v1 - v0) + v * (v2 - v0);
				dist = distTemp;
				success = tempSuccess;
			}

			v0 = vFloorArr[dwIndex + VTXCNTX];
			v1 = vFloorArr[dwIndex + 1];
			v2 = vFloorArr[dwIndex];

			tempSuccess = D3DXIntersectTri(&v0, &v1, &v2
				, (const D3DXVECTOR3*)(&pRay->vOrigin)
				, (const D3DXVECTOR3*)(&pRay->vDirection)
				, &u, &v, &distTemp);

			if (tempSuccess && (dist > distTemp))
			{
				*result = v0 + u*(v1 - v0) + v * (v2 - v0);
				dist = distTemp;
				success = tempSuccess;
			}
		}
	}

	return success;
}

_bool CEditCamera::IntersectRayTri(IN CVIBuffer* pVIBuffer, OUT Triangle& tri)
{
	if (Get_DIMouseState(DIM_RB) & 0x80)
	{
		Triangle tTri;
		Ray ray = CalcRaycast(GetMousePos());
		_bool success = Compute_RayCastHitBuffer(&ray, pVIBuffer, tTri);

		if (success)
		{
			memcpy(&tri, &tTri, sizeof(Triangle));
			return true;
		}
	}
	return false;
}



Ray CEditCamera::CalcRaycast(POINT ptMouse)
{
	Ray ray;
	_vec3 vMouse;

	// 뷰포트 -> 투영
	D3DVIEWPORT9		ViewPort;
	ZeroMemory(&ViewPort, sizeof(D3DVIEWPORT9));
	m_pGraphicDev->GetViewport(&ViewPort);
	vMouse.x = ptMouse.x / (ViewPort.Width * 0.5f) - 1.f;
	vMouse.y = ptMouse.y / -(ViewPort.Height * 0.5f) + 1.f;
	vMouse.z = 0.f;

	//  투영 -> 뷰 스페이스
	_matrix		matProj;
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);
	D3DXMatrixInverse(&matProj, 0, &matProj);
	D3DXVec3TransformCoord(&vMouse, &vMouse, &matProj);

	// 뷰 스페이스 -> 월드
	_matrix		matView;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matView, 0, &matView);
	ray.vOrigin = { 0.f,0.f,0.f };
	ray.vDirection = vMouse - ray.vOrigin;

	D3DXVec3TransformCoord(&ray.vOrigin, &ray.vOrigin, &matView);
	D3DXVec3TransformNormal(&ray.vDirection, &ray.vDirection, &matView);

	return ray;
}

POINT CEditCamera::GetMousePos()
{
	POINT ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	return ptMouse;
}