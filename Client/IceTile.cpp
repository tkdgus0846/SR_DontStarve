#include "IceTile.h"
#include "Export_Function.h"

CIceTile::CIceTile(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

CIceTile::~CIceTile()
{
}

CGameObject * CIceTile::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CIceTile* pInstance = new CIceTile(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

CGameObject * CIceTile::LoadSaveTarget(LPDIRECT3DDEVICE9 pGraphicDev)
{
	return Create(pGraphicDev);
}

HRESULT CIceTile::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorIce", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorIce", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	//CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_TRIGGER));
	//pCollider->Set_BoundingBox({ 10.f, 5.f, 10.f });
	//m_uMapComponent[ID_ALL].insert({ L"BodyCollider", pCollider });

	return result;
}

void CIceTile::OnCollisionEnter(const Collision * collision)
{
	if (IsBodyCollider(collision))
	{
		//TODO
		m_vDir = collision->OtherGameObject->m_pTransform->m_vInfo[INFO_LOOK];
		m_vDir.Normalize();
	}
}

void CIceTile::OnCollisionStay(const Collision * collision)
{
	if (IsBodyCollider(collision))
	{
		cout << m_vDir.x << "\t" << m_vDir.y << "\t" << m_vDir.z << endl;
		//TODO
		collision->OtherGameObject->m_pTransform->Move_WalkWithVec(m_vDir, 10.f, 0.016f);
	}
}

void CIceTile::OnCollisionExit(const Collision * collision)
{
	if (IsBodyCollider(collision))
	{
		//TODO
		m_vDir = {};
	}
}