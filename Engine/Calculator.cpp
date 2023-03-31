#include "stdafx.h"
#include "Calculator.h"

#include "Export_Function.h"



CCalculator::CCalculator()
{
}


CCalculator::~CCalculator()
{
}

//_float CCalculator::Compute_HeightOnTerrain(const _vec3 * pPos, const _vec3 * pTerrainVtxPos, const _ulong & dwCntX, const _ulong & dwCntZ, const _ulong & dwVtxItv)
//{
//	return 0.f;
//	//_ulong	dwIndex = _ulong(pPos->z / dwVtxItv) * dwCntX + _ulong(pPos->x / dwVtxItv);
//
//	//_float	fRatioX = (pPos->x - pTerrainVtxPos[dwIndex + dwCntX].x) / dwVtxItv;
//	//_float	fRatioZ = (pTerrainVtxPos[dwIndex + dwCntX].z - pPos->z) / dwVtxItv;
//
//	//D3DXPLANE		Plane;
//
//	//// 오른쪽 위
//	//if (fRatioX > fRatioZ)
//	//{
//	//	D3DXPlaneFromPoints(&Plane,
//	//		&pTerrainVtxPos[dwIndex + dwCntX],
//	//		&pTerrainVtxPos[dwIndex + dwCntX + 1],
//	//		&pTerrainVtxPos[dwIndex + 1]);
//	//}
//
//	//else
//	//{
//	//	D3DXPlaneFromPoints(&Plane,
//	//		&pTerrainVtxPos[dwIndex + dwCntX],
//	//		&pTerrainVtxPos[dwIndex + 1],
//	//		&pTerrainVtxPos[dwIndex]);
//	//}
//
//	////ax + by + cz + d  = 0;
//
//	////by = -ax - cz - d
//
//	////y = (-ax - cz - d) / b;
//
//	//return (-Plane.a * pPos->x - Plane.c * pPos->z - Plane.d) / Plane.b;
//}
//
//_vec3 CCalculator::Picking_OnTerrain(HWND hWnd, LPDIRECT3DDEVICE9 pGraphicDev, Engine::CTerrainTex * pTerrainBufferCom, CTransform * pTerrainTransCom)
//{
//	return _vec3();
//	//POINT	ptMouse{};
//	//GetCursorPos(&ptMouse);
//	//ScreenToClient(hWnd, &ptMouse);
//
//	//// 뷰포트 -> 투영
//
//	//D3DVIEWPORT9		ViewPort;
//	//ZeroMemory(&ViewPort, sizeof(D3DVIEWPORT9));
//	//pGraphicDev->GetViewport(&ViewPort);
//
//	//_vec3	vMouse;
//
//	//vMouse.x = ptMouse.x / (ViewPort.Width * 0.5f) - 1.f;
//	//vMouse.y = ptMouse.y / -(ViewPort.Height * 0.5f) + 1.f;
//	//vMouse.z = 0.f;
//
//	////  투영 -> 뷰 스페이스
//	//_matrix		matProj;
//	//pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);
//	//D3DXMatrixInverse(&matProj, 0, &matProj);
//	//D3DXVec3TransformCoord(&vMouse, &vMouse, &matProj);
//
//	//// 뷰 스페이스 -> 월드
//	//_matrix		matView;
//	//pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
//	//D3DXMatrixInverse(&matView, 0, &matView);
//
//	//_vec3	vRayPos, vRayDir;
//
//	//vRayPos = { 0.f,0.f,0.f };
//	//vRayDir = vMouse - vRayPos;
//
//	//D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matView);
//	//D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matView);
//
//	//// 월드 -> 로컬
//
//	//_matrix		matWorld = *pTerrainTransCom->Get_WorldMatrixPointer();
//	//D3DXMatrixInverse(&matWorld, 0, &matWorld);
//
//	//D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matWorld);
//	//D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matWorld);
//
//	//_ulong	dwVtxIdx[3]{};
//	//_float	fU, fV, fDist;
//
//	//const _vec3*		pTerrainPos = pTerrainBufferCom->Get_VtxPos();
//
//	//for (_ulong i = 0; i < VTXCNTZ; ++i)
//	//{
//	//	for (_ulong j = 0; j < VTXCNTX; ++j)
//	//	{
//	//		_ulong dwIndex = i * VTXCNTX + j;
//
//	//		// 오른쪽 위
//	//		dwVtxIdx[0] = dwIndex + VTXCNTX;
//	//		dwVtxIdx[1] = dwIndex + VTXCNTX + 1;
//	//		dwVtxIdx[2] = dwIndex + 1;
//
//	//		// V1 + U(V2 - V1) + V(V3 - V1)
//	//		if (D3DXIntersectTri(&pTerrainPos[dwVtxIdx[1]],
//	//			&pTerrainPos[dwVtxIdx[0]],
//	//			&pTerrainPos[dwVtxIdx[2]],
//	//			&vRayPos, &vRayDir, &fU, &fV, &fDist))
//	//		{
//	//			return _vec3(pTerrainPos[dwVtxIdx[1]].x + fU * (pTerrainPos[dwVtxIdx[0]].x - pTerrainPos[dwVtxIdx[1]].x),
//	//				0.f,
//	//				pTerrainPos[dwVtxIdx[1]].z + fV * (pTerrainPos[dwVtxIdx[2]].z - pTerrainPos[dwVtxIdx[1]].z));
//	//		}
//
//	//		// 왼쪽 아래
//	//		dwVtxIdx[0] = dwIndex + VTXCNTX;
//	//		dwVtxIdx[1] = dwIndex + 1;
//	//		dwVtxIdx[2] = dwIndex;
//
//	//		// V1 + U(V2 - V1) + V(V3 - V1)
//	//		if (D3DXIntersectTri(&pTerrainPos[dwVtxIdx[2]],
//	//			&pTerrainPos[dwVtxIdx[1]],
//	//			&pTerrainPos[dwVtxIdx[0]],
//	//			&vRayPos, &vRayDir, &fU, &fV, &fDist))
//	//		{
//	//			return _vec3(pTerrainPos[dwVtxIdx[2]].x + fU * (pTerrainPos[dwVtxIdx[1]].x - pTerrainPos[dwVtxIdx[2]].x),
//	//				0.f,
//	//				pTerrainPos[dwVtxIdx[2]].z + fV * (pTerrainPos[dwVtxIdx[0]].z - pTerrainPos[dwVtxIdx[2]].z));
//	//		}
//	//	}
//	//}
//
//	return _vec3();
//}
