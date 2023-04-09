#include "EditCamera.h"
#include "Room.h"
#include "Wall.h"
#include "MyMap.h"
#include "Export_Function.h"
#include "MyMap.h"
#include "FloorTile.h"

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
	CCamera* pCamera = dynamic_cast<CCamera*>(Engine::Clone_Proto(L"Camera", this));
	NULL_CHECK_RETURN(pCamera, E_FAIL);
	m_uMapComponent[ID_UPDATE].insert({ L"Edit_Camera", pCamera });
	pCamera->Set_CameraName(L"Edit_Camera");

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
		_vec3 vCameraPos = m_pTransform->m_vInfo[INFO_POS];
		CMyMap* pMap = (CMyMap*)Get_GameObject(LAYER_ENVIRONMENT, L"Map");
		// Variables for Output about InstersectRayRoom Method
		Triangle tri;
		INDEX32 index;
		CGameObject* pGameObj = nullptr;
		float fDist;
		if (IntersectRayRoom(pMap->Get_CurRoom(vCameraPos), pGameObj, tri, index, fDist))
		{
			CFloorTile* pTile = nullptr;
			// Decide Tile Position
			_vec3 vPos{0.f, 0.f, 0.f};
			vPos = CalcMiddlePoint(tri);
			_vec3 vOffset = vPos - vCameraPos;
			vPos.y += 0.01f;
			CRoom* pCurRoom = pMap->Get_CurRoom(vCameraPos);
			pTile = CFloorTile::Create(m_pGraphicDev, vPos);
			pCurRoom->AddTile(pTile);

			// Decide Tile Rotation;
			_vec3 vTileNormal = tri.Normal();
			vTileNormal.Normalize();

			if (vTileNormal.Degree(_vec3::Up()) > 0.1f)
			{
				pTile->m_pTransform->Set_Dir(vTileNormal);
			}
			pTile->m_pTransform->Move_Walk(-0.01f, 1.f);
		}

		/*cout << fixed;
		cout.precision(0);
		cout << tri.v[0].x << " " << tri.v[0].y << " " << tri.v[0].z << "\t"
			<< tri.v[1].x << " " << tri.v[1].y << " " << tri.v[1].z << "\t"
			<< tri.v[2].x << " " << tri.v[2].y << " " << tri.v[2].z << endl;*/
	}
}

void CEditCamera::Mouse_Move(const _float & fTimeDelta)
{
	_long dwMouseMove = 0;

	if (dwMouseMove = Engine::Get_DIMouseMove(DIMS_Y))
		m_pTransform->m_vInfo[INFO_LOOK] += _vec3(0.f, 1.f, 0.f) * _float(-dwMouseMove) * fTimeDelta / 10.f;

	if (dwMouseMove = Engine::Get_DIMouseMove(DIMS_X))
		m_pTransform->Rot_Yaw(_float(dwMouseMove) * 5.f, fTimeDelta);
}

void CEditCamera::Fix_Mouse()
{
	POINT ptMouse{ WINCX >> 1, WINCY >> 1 };

	ClientToScreen(g_hWnd, &ptMouse);
	SetCursorPos(ptMouse.x, ptMouse.y);
}

/*
Ray PickingRay(POINT pt);
1. 카메라 위치에서 마우스로 광선을 쏨.
-> 뷰포트 to 투영
-> 투영 to 뷰 스페이스
-> 뷰 스페이스 to 월드
-> ray객체 반환.


_bool IntersectRayTri(Ray ray, CVIBuffer _pVB, OUT float& distance, OUT _vec3& _InterPos)
2. 현재 room안에 있는 모든 객체들의 버텍스 버퍼와 광선이 교차하는지 검사한다.
-> VIBuffer컴포넌트를 매개 변수의 인자로 받는다.
-> 광선과 VIBuffer의 삼각형들이 교차하는지 검사한다.*/

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

_bool CEditCamera::Compute_RayCastHitGameObject(IN Ray* pRay, IN CGameObject* pGameObject, OUT Triangle& tri, OUT INDEX32& index, OUT float& fDist)
{
	CVIBuffer* pVIBuffer = pGameObject->Get_VIBuffer();
	CTransform* pTransform = pGameObject->m_pTransform;
	
	_matrix matWorld = *pTransform->Get_WorldMatrixPointer();

	if (!pVIBuffer) 
		return false;

	_bool success = false;
	_float u, v;
	_float dist = FLT_MAX;
	_float distTemp = 0.f;
	VTXTEX* vertices = nullptr;
	INDEX32* indices = nullptr;
	_bool tempSuccess;
	Triangle	tmpTri;
	D3DVERTEXBUFFER_DESC vbDescription;
	D3DINDEXBUFFER_DESC inDescription;

	pVIBuffer->GetVertexBuffer()->GetDesc(&vbDescription);
	pVIBuffer->GetIndexBuffer()->GetDesc(&inDescription);

	pVIBuffer->GetVertexBuffer()->Lock(0, 0, (void**)&vertices, 0);
	pVIBuffer->GetIndexBuffer()->Lock(0, 0, (void**)&indices, 0);

	_ulong dwSize = inDescription.Size / sizeof(INDEX32);
	for (_ulong i = 0; i < dwSize; ++i)
	{
		tmpTri.v[0] = vertices[indices[i]._0].vPos;
		tmpTri.v[1] = vertices[indices[i]._1].vPos;
		tmpTri.v[2] = vertices[indices[i]._2].vPos;

		tmpTri.v[0].TransformCoord(&matWorld);
		tmpTri.v[1].TransformCoord(&matWorld);
		tmpTri.v[2].TransformCoord(&matWorld);
			
		tempSuccess = D3DXIntersectTri(&tmpTri.v[0]
			, &tmpTri.v[1]
			, &tmpTri.v[2]
			, (const D3DXVECTOR3*)(&pRay->vOrigin)
			, (const D3DXVECTOR3*)(&pRay->vDirection)
			, &u, &v, &distTemp);

		if (tempSuccess && (dist > distTemp))
		{
			fDist = dist = distTemp;
			success = tempSuccess;
			tri = tmpTri;
			index = indices[i];
		}
	}

	pVIBuffer->GetVertexBuffer()->Unlock();
	pVIBuffer->GetIndexBuffer()->Unlock();

	return success;
}

_bool CEditCamera::IntersectRayRoom(IN CRoom* pRoom, OUT CGameObject*& pGameObject,OUT Triangle& tri, OUT INDEX32& index, OUT float& fDist)
{
	CGameObject* pTempObj = nullptr;
	_bool success = false;
	Triangle tmpTri;
	INDEX32 tmpIndex;
	float fMinDist = FLT_MAX;

	for (_int i = 0; i < pRoom->ObjNum(); ++i)
	{
		if (IntersectRayGameObject(pGameObject = pRoom->GetObjByIndex(i), tri, index, fDist))
		{
			if (fMinDist > fDist)
			{
				fMinDist = fDist;
				pTempObj = pGameObject;
				tmpTri = tri;
				tmpIndex = index;
			}
			success = true;
		}
	}

	for (_int i = 0; i < pRoom->TileNum(); ++i)
	{
		if (IntersectRayGameObject(pGameObject = pRoom->GetTileByIndex(i), tri, index, fDist))
		{
			if (fMinDist > fDist)
			{
				fMinDist = fDist;
				pTempObj = pGameObject;
				tmpTri = tri;
				tmpIndex = index;
			}
			success = true;
		}
	}

	for (_int i = 0; i < 4; ++i)
	{
		if (IntersectRayGameObject(pGameObject = pRoom->GetWallArray(i), tri, index, fDist))
		{
			if (fMinDist > fDist)
			{
				fMinDist = fDist;
				pTempObj = pGameObject;
				tmpTri = tri;
				tmpIndex = index;
			}
			success = true;
		}
			
	}
	
	if (IntersectRayGameObject(pGameObject = pRoom->GetFloor(), tri, index, fDist))
	{
		if (fMinDist > fDist)
		{
			fMinDist = fDist;
			pTempObj = pGameObject;
			tmpTri = tri;
			tmpIndex = index;
		}
		
		success = true;
	}

	if (success)
	{
		fDist = fMinDist;
		pGameObject = pTempObj;
		tri = tmpTri;
		index = tmpIndex;
	}
		

	return success;
}

_bool CEditCamera::IntersectRayGameObject(IN CGameObject* pGameObject, OUT Triangle& tri, OUT INDEX32& index, OUT float& fDist)
{
	Triangle tTri;
	INDEX32 index32;
	Ray ray = CalcRaycast(GetMousePos());
	
	_bool success = Compute_RayCastHitGameObject(&ray, pGameObject, tTri, index32, fDist);

	if (success)
	{
		memcpy(&tri, &tTri, sizeof(Triangle));
		memcpy(&index, &index32, sizeof(INDEX32));
		return true;
	}

	return false;
}



Ray CEditCamera::CalcRaycast(POINT ptMouse)
{
	float px = 0.f;
	float py = 0.f;

	D3DVIEWPORT9 vp;
	m_pGraphicDev->GetViewport(&vp);

	D3DXMATRIX proj;
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &proj);

	px = (((2.f * ptMouse.x) / vp.Width) - 1.0f) / proj(0, 0);
	py = (((-2.f * ptMouse.y) / vp.Height) + 1.0f) / proj(1, 1);

	Ray ray;
	ray.vOrigin = D3DXVECTOR3(0.f, 0.f, 0.f);
	ray.vDirection = D3DXVECTOR3(px, py, 1.f);

	_matrix matView;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matView, 0, &matView);

	D3DXVec3TransformCoord(&ray.vOrigin, &ray.vOrigin, &matView);
	D3DXVec3TransformNormal(&ray.vDirection, &ray.vDirection, &matView);
	D3DXVec3Normalize(&ray.vDirection, &ray.vDirection);


	//cout << ray.vDirection.x << "\t" << ray.vDirection.y << "\t" << ray.vDirection.z << endl;

	return ray;
}

POINT CEditCamera::GetMousePos()
{
	POINT ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	return ptMouse;
}

_vec3 CEditCamera::CalcMiddlePoint(Triangle & tri)
{
	_vec3 standard;
	_vec3 a;
	_vec3 b;
	_vec3 A;
	_vec3 B;
	_vec3 result;
	standard = tri.v[0];
	a = tri.v[1];
	b = tri.v[2];
	A = a - standard;
	B = b - standard;

	if (fabs(A.Dot(B)) < 0.1f)
	{
		result = (a + b) / 2.f;
		return result;
	}

	standard = tri.v[1];
	a = tri.v[0];
	b = tri.v[2];
	A = a - standard;
	B = b - standard;

	if (fabs(A.Dot(B)) < 0.1f)
	{
		result = (a + b) / 2.f;
		return result;
	}
		 
	
	standard = tri.v[2];
	a = tri.v[1];
	b = tri.v[0];
	A = a - standard;
	B = b - standard;

	if (fabs(A.Dot(B)) < 0.1f)
	{
		result = (a + b) / 2.f;
		return result;
	}

	return _vec3();
}
