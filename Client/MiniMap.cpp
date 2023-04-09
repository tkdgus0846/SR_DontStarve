#include "MiniMap.h"
#include "Export_Function.h"

CMiniMap::CMiniMap(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUI(pGraphicDev)
{
}

CMiniMap::~CMiniMap()
{
}

HRESULT CMiniMap::Add_Component()
{
	m_pRcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(m_pRcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", m_pRcTex });

	CTexture* Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"MiniMap_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"MiniMap_Texture", Texture });

	Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"MapPos_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_arrMap[MINIMAPPOS] = Texture;

	Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"MiniMapBackGround_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_arrMap[MINIMAPBACKGROUND] = Texture;

	return S_OK;
}

HRESULT CMiniMap::Ready_GameObject(void)
{
	__super::Ready_GameObject();

	return S_OK;
}

_int CMiniMap::Update_GameObject(const _float & fTimeDelta)
{
	Engine::Add_RenderGroup(RENDER_ALPHA_UI, this);
	
	m_PlayerAngle += 1;

	__super::Update_GameObject(fTimeDelta);

	return 0;
}

void CMiniMap::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}


void CMiniMap::Render_GameObject(void)
{
//	D3DVIEWPORT9 viewport;
//	m_pGraphicDev->GetViewport(&viewport);
//	D3DVIEWPORT9 savedViewport = viewport;
//
//	int miniMapWidth = 300; // 미니맵 가로 크기
//	int miniMapHeight = 300; // 미니맵 세로 크기
//
//	RECT miniMapRect = { 600, 300, 800, 0 };
//
//	LPDIRECT3DSURFACE9 pMiniMapSurface; // 미니맵을 그리기 위한 서피스 객체
//	m_pGraphicDev->CreateOffscreenPlainSurface(0.f, 0.f, D3DFMT_X8R8G8B8, D3DPOOL_SYSTEMMEM, &pMiniMapSurface, NULL);
//	m_pGraphicDev->SetRenderTarget(0, pMiniMapSurface); // 미니맵 서피스를 렌더링 타겟으로 설정
//	m_pGraphicDev->SetViewport(&D3DVIEWPORT9{ (DWORD)500, (DWORD)300, (DWORD)miniMapWidth, (DWORD)miniMapHeight, 0.0f, 1.0f });
//
	for (size_t i = 0; i < MINIMAPEND; i++)
	{
		if (m_arrMap[i] != nullptr)
		{
			switch (i)
			{
			case MINIMAPBACKGROUND:
				Set_ViewMatrix_UI(300.f, -130.f, 76.f, 10.f);
				break;
			case MINIMAPPOS:
				Set_ViewMatrix_UI(300.f, -210.f, 16.f, 16.f, m_PlayerAngle);
				break;
			case MINIMAPBLANKBLACK:
				Set_ViewMatrix_UI();
				break;
			case MINIMAPBLANKGRAY:
				Set_ViewMatrix_UI();
				break;
			}
			dynamic_cast<CTexture*>(m_arrMap[i])->Render_Texture();
			m_pRcTex->Render_Component();
		}
	}

	Set_ViewMatrix_UI();
	__super::Render_GameObject();

	//m_pGraphicDev->SetViewport(&savedViewport);
	

	//D3DXMATRIXA16 matProj;
	//D3DXMatrixOrthoLH(&matProj, 200.f, 200.f, -1.0f, 1.0f);
	//m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matProj);

	//_vec3 PlayerPos;
	//Engine::Get_Player()->m_pTransform->Get_Info(INFO_POS, &PlayerPos);

	//D3DXVECTOR3 vEyePt(PlayerPos.x, PlayerPos.y, PlayerPos.z); // 미니맵에서 보이는 카메라 위치
	//D3DXVECTOR3 vLookatPt(PlayerPos.x, 0.0f, PlayerPos.z); // 플레이어 위치를 중심으로 볼 수 있도록 함
	//D3DXVECTOR3 vUpVec(0.0f, 0.0f, 1.0f); // 미니맵에서는 위쪽 방향을 고정함

	//D3DXMATRIXA16 matView;
	//D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	//m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);

	//// 미니맵 그리기
}

void CMiniMap::Set_ViewMatrix_UI()
{
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);

	_matrix matTrans;
	D3DXMatrixScaling(&matView, 76.f, 92.f, 0.f);
	matTrans.Translation(300.f, -200.f, 0.f);
	D3DXMatrixMultiply(&matView, &matView, &matTrans);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
}

void CMiniMap::Set_ViewMatrix_UI(_float posX, _float posY, _float scaleX, _float scaleY)
{
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);

	_matrix matTrans;
	D3DXMatrixScaling(&matView, scaleX, scaleY, 0.f);
	matTrans.Translation(posX, posY, 0.f);
	D3DXMatrixMultiply(&matView, &matView, &matTrans);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
}

void CMiniMap::Set_ViewMatrix_UI(_float posX, _float posY, _float scaleX, _float scaleY, _float fAngle)
{
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);

	_matrix pPlayerWorld = *Engine::Get_Player()->m_pTransform->Get_WorldMatrixPointer();
	_vec3 vecRot;
	D3DXMatrixScaling(&matView, scaleX, scaleY, 0.f);
	//_float fDot = D3DXVec3Dot(&PlayerLook, &AxisRight);
	//_float fAngleZ = acosf(fDot);

	D3DXVec3TransformNormal(&vecRot, &vecRot, &pPlayerWorld);
	_float fAngleZ = atan2f(vecRot.x, vecRot.z);

	_matrix matRot, matTrans;
	matRot.RotationZ(fAngleZ);
	matTrans.Translation(posX, posY, 0.f);
	D3DXMatrixMultiply(&matView, &matView, &matRot);
	D3DXMatrixMultiply(&matView, &matView, &matTrans);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
}

CMiniMap * CMiniMap::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMiniMap* pInstance = new CMiniMap(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CMiniMap::Free(void)
{
	Safe_Release(m_pRcTex);
	
	auto iter = m_arrMap.begin();
	for (; iter < m_arrMap.end(); iter++)
	{
		Safe_Release(*iter);
	}
	__super::Free();
}