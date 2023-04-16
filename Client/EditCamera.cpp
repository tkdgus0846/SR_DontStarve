#include "EditCamera.h"
#include "Room.h"
#include "Wall.h"
#include "Tile.h"
#include "RoomMgr.h"
#include "Export_Function.h"
#include "RoomMgr.h"
#include "Floor.h"
#include "TileFactory.h"
#include "MonsterFactory.h"
#include "MapObjectFactory.h"
#include "ImManager.h"
#include "ImInspector.h"
#include "FileSystem.h"
CEditCamera::CEditCamera(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
	, m_fSpeed(0.f)
	, m_bFix(true)
	, m_pCurTextureName(L"Floor_Level1_Texture")
{
	Set_LayerID(LAYER_CAMERA);
	Set_ObjTag(L"Edit_Camera");
	ZeroMemory(&m_tPickInfo, sizeof(ClickInfo));
}

CEditCamera::~CEditCamera()
{
}

HRESULT CEditCamera::Ready_GameObject(void)
{
	HRESULT result = __super::Ready_GameObject();

	m_pTransform->m_vScale = { 1.f, 1.f, 1.f };
	m_pTransform->m_vInfo[INFO_POS] = _vec3(15.f, 20.f, 30.f);
	m_pTransform->m_vInfo[INFO_LOOK] = { 0.f, 0.f, 1.f };
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
	CCamera* pCamera = dynamic_cast<CCamera*>(Engine::Clone_Proto(L"Camera", this));
	NULL_CHECK_RETURN(pCamera, E_FAIL);
	m_uMapComponent[ID_UPDATE].insert({ L"Edit_Camera", pCamera });
	pCamera->Set_CameraName(L"Edit_Camera");

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_PLAYER));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"BodyCollider", pCollider });
	pCollider->Set_BoundingBox({ 2.f,2.f,2.f });

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

	if (Engine::Key_Down((DIK_C))) Engine::Toggle_ColliderRender();
	if (Engine::Key_Down(DIK_1)) m_bFix = !m_bFix;

	if (Engine::Mouse_Down(DIM_LB))
	{
		SetClickInfo();
		CreateTile();
		CreateMonster();
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

void CEditCamera::SetClickInfo()
{
	_matrix proj;
	proj.PerspectiveFovLH();
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &proj);

	CRoomMgr* pRoomMgr = ROOM_MGR;
	// Variables for Output about InstersectRayRoom Method

	IntersectRayRoom(pRoomMgr->Get_CurRoom(), m_tPickInfo.pGameObj, m_tPickInfo.tri, m_tPickInfo.index, m_tPickInfo.fDist);
}

_bool CEditCamera::IntersectRayRoom(IN const CRoom* pRoom, OUT CGameObject*& pGameObject, OUT Triangle& tri, OUT INDEX32& index, OUT float& fDist)
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

void CEditCamera::LoadSaveTarget(const _tchar* tag)
{
	if (PICK_TILE != m_ePick)
		return;

	//CTile* pTile = LOADER->Load(tag);
	//if (!pTile)
	//	return;

	// Decide Tile Position

	_vec3 vPos{ 0.f, 0.f, 0.f };
	vPos = CalcMiddlePoint(m_tPickInfo.tri);
	_vec3 vOffset = vPos - m_pTransform->m_vInfo[INFO_POS];
	vPos.y += 0.01f;
	CRoom* pCurRoom = ROOM_MGR->Get_CurRoom();

	if (dynamic_cast<CTile*>(m_tPickInfo.pGameObj)) {}	// 기존에 이미 설치된 타일인 경우
/*		dynamic_cast<CTile*>(m_tPickInfo.pGameObj)->Change_Texture(m_pCurTextureName);*/ // 부수고 재설치

	else	// 설치된 타일이 없는 경우
	{
		/*pTile = CTile::Create(m_pGraphicDev, vPos, m_pCurTextureName);
		pCurRoom->PushBack_GameObj(pTile);*/ // 설치

		// Decide Tile Rotation;
		//_vec3 vTileNormal = m_tPickInfo.tri.Normal();
		//vTileNormal.Normalize();

		//if (vTileNormal.Degree(_vec3::Up()) > 0.1f)
		//{
		//	pTile->m_pTransform->Set_Dir(vTileNormal);
		//}
		//pTile->m_pTransform->Move_Walk(-0.01f, 1.f);
	}
}

void CEditCamera::CreateMonster()
{
	if (PICK_MONSTER != m_ePick)
		return;
	
	if (!dynamic_cast<CFloor*>(m_tPickInfo.pGameObj))
		return;

	CImInspector* pWindow = dynamic_cast<CImInspector*>(CImManager::GetInstance()->FindByTag(L"Inspector"));

	CGameObject* pObj = MONSTER_FACTORY->CreateObject(TO_WSTR(pWindow->Get_CurMonsterItem()));
	if (!pObj)
		return;

	ROOM_MGR->Get_CurRoom()->PushBack_GameObj(pObj);
	_vec3 vPos = CalcMiddlePoint(m_tPickInfo.tri);

	switch (m_radio)
	{
	case 0:
		vPos.x -= (VTXCNTX - 1) * 0.5f;
		vPos.z += (VTXCNTZ - 1) * 0.5f;
		break;
	case 1:
		vPos.x += (VTXCNTX - 1) * 0.5f;
		vPos.z += (VTXCNTZ - 1) * 0.5f;
		break;
	case 2:
		vPos.x -= (VTXCNTX - 1) * 0.5f;
		vPos.z -= (VTXCNTZ - 1) * 0.5f;
		break;
	case 3:
		vPos.x += (VTXCNTX - 1) * 0.5f;
		vPos.z -= (VTXCNTZ - 1) * 0.5f;
		break;
	}

	pObj->m_pTransform->Set_Pos(vPos);
}

void CEditCamera::CreateTile()
{
	if (PICK_TILE != m_ePick)
		return;

	if (!dynamic_cast<CFloor*>(m_tPickInfo.pGameObj))
		return;

	// IMGUI 콤보박스 정보 가져옴.
	CImInspector* pInspector = static_cast<CImInspector*>(IM_MGR->FindByTag(L"Inspector"));
	wstring CurTileItem = TO_WSTR(pInspector->Get_CurTileItem());
	
	// 타일 생성
	CGameObject* pObj = TILE_FACTORY->CreateObject(CurTileItem);
	if (!pObj) return;
	ROOM_MGR->Get_CurRoom()->PushBack_GameObj(pObj);
	
	// 타일 위치 정해주기.
	_vec3 vPos = CalcMiddlePoint(m_tPickInfo.tri);
	vPos.y += 0.01f;
	pObj->m_pTransform->Set_Pos(vPos);
	
}