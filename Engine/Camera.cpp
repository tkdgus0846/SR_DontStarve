#include "stdafx.h"
#include "Camera.h"

#include "Component.h"

#include "Export_Function.h"


CCamera::CCamera(LPDIRECT3DDEVICE9 pGraphicDev)
	:CComponent(pGraphicDev), m_bSwitch(false),
	m_pName(nullptr)
{
	//ZeroMemory(m_szName, sizeof(_tchar) * 256);
	ZeroMemory(&m_tViewParams, sizeof(VIEWPARAMS));
	ZeroMemory(&m_tProjParams, sizeof(PROJPARAMS));
}

CCamera::CCamera(const CCamera & rhs)
	:CComponent(rhs), m_bSwitch(false),
	m_pName(rhs.m_pName)
{
	//ZeroMemory(m_szName, sizeof(_tchar) * 256);
	m_tViewParams = rhs.m_tViewParams;
	m_tProjParams = rhs.m_tProjParams;
	m_matView = rhs.m_matView;
	m_matProj = rhs.m_matProj;

	m_bFix = true;
}

CCamera::~CCamera()
{
}

HRESULT CCamera::Ready_Camera(VIEWPARAMS& tViewParam, PROJPARAMS& tProjParam)
{
	m_tViewParams = tViewParam;
	m_tProjParams = tProjParam;

	m_tViewParams.LookAtLH(&m_matView);
	m_tProjParams.PerspectiveLH(&m_matProj);

	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matProj);

	return S_OK;
}

_int CCamera::Update_Component(const _float & fTimeDelta)
{
	if (!m_bSwitch)
		return 0;


	m_tViewParams.vEye = m_pGameObject->m_pTransform->m_vInfo[INFO_POS];

	m_tViewParams.vAt = m_tViewParams.vEye + m_pGameObject->m_pTransform->m_vInfo[INFO_LOOK];


	if (m_bShack)
		Shake(fTimeDelta);

	//cout << vLook.x << " " << vLook.y << " " << vLook.z << endl;


	m_tViewParams.LookAtLH(&m_matView);

	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_matView);

	return 0;
}

void CCamera::Shake(const _float & fTimeDelta)
{
	static _float fTime = 0.f;
	static _float fX = 0.f, fY = 0.f;

	fTime += fTimeDelta;

	fY = sinf(fX * 3.f) * powf(0.4f, fX);
	fY *= (rand() % 2);

	m_tViewParams.vEye.y += fY;

	fX += fTimeDelta * 5.f;

	if (fX > 5.f)
	{
		fX = 0.f;
		fY = 0.f;
		m_bShack = false;
	}
	/*if (fTime > fTimeDelta * 2)
	{

		_vec3 vAmount = { _float(rand() % 2), _float(rand() % 2) , _float(rand() % 2) };

		D3DXVec3Normalize(&vAmount, &vAmount);
		m_tViewParams.vEye += vPadong;
		fTime = 0.f;
		
	}*/

}

CCamera * CCamera::Create(LPDIRECT3DDEVICE9 pGraphicDev, VIEWPARAMS& tViewParam, PROJPARAMS& tProjParam)
{
	CCamera* pInstance = new CCamera(pGraphicDev);

	if (FAILED(pInstance->Ready_Camera(tViewParam, tProjParam)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CCamera::Clone(void)
{
	CCamera* pInstance = new CCamera(*this);
	NULL_CHECK_RETURN(pInstance, nullptr);

	// ���⼭ ī�޶� �Ŵ��� �߰�.
	Engine::CCameraMgr::GetInstance()->Add_Camera(m_pName, pInstance);
	
	return pInstance;
}

void CCamera::Free()
{
	__super::Free();
}
