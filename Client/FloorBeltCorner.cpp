#include "FloorBeltCorner.h"
#include "Export_Function.h"
#include "Player.h"
#include "Enemy.h"


CFloorBeltCorner::CFloorBeltCorner(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}


CFloorBeltCorner::~CFloorBeltCorner()
{
}

CGameObject * CFloorBeltCorner::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CFloorBeltCorner* pInstance = new CFloorBeltCorner(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}


void CFloorBeltCorner::InteractGameObject(const InteractInfo * tInteractInfo)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(tInteractInfo->pGameObject);

	CEnemy* pEnemy = dynamic_cast<CEnemy*>(tInteractInfo->pGameObject);

	
	float fBeltSpeed = 3.f;
	_vec3 vPos;
	_vec3 vDir;
	if (pPlayer)
	{
		vPos = pPlayer->m_pTransform->m_vInfo[INFO_POS];
		Vertex4 vtx4 = Get_PlaneXZ();
		
		float fRatioX = _vec3::Ratio(vtx4._v1, vtx4._v2, vPos);
		float fRatioZ = _vec3::Ratio(vtx4._v1, vtx4._v3, vPos);
		fRatioX = fabs(fRatioX);
		fRatioZ = fabs(fRatioZ);
		
		(fRatioX < fRatioZ) ? vDir = m_pTransform->m_vInfo[INFO_UP]
			: vDir = m_pTransform->m_vInfo[INFO_RIGHT];

		pPlayer->m_pTransform->Move_WalkWithVec(vDir, fBeltSpeed, tInteractInfo->_fTimeDelta);
	}

	if (pEnemy)
	{
		pEnemy->m_pTransform->Move_WalkWithVec(vDir, fBeltSpeed, tInteractInfo->_fTimeDelta);
	}
}

HRESULT CFloorBeltCorner::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorBeltCorner", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorBeltCorner", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}

void CFloorBeltCorner::OnCollisionStay(const Collision * collision)
{
	if (IsBodyCollider(collision))
	{
		//TODO
	}
}