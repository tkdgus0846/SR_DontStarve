#include "SoftPyramid.h"
#include "Export_Function.h"
#include "Bullet.h"
#include "WeaponItem.h"
#include "Tile.h"
#include "RoomMgr.h"
#include "Room.h"

CSoftPyramid::CSoftPyramid(LPDIRECT3DDEVICE9 pGraphicDev)
	: CPyramid(pGraphicDev)
{
	Set_ObjTag(L"SoftPyramid");
}

CSoftPyramid::~CSoftPyramid()
{
}

void CSoftPyramid::OnCollisionEnter(const Collision * collsion)
{
	if (dynamic_cast<CBullet*>(collsion->OtherGameObject))
	{
		this->SetDead();
	}
}

void CSoftPyramid::OnCollisionStay(const Collision * collision)
{
	if (collision->MyCollider == Get_Component(L"BodyCollider", ID_ALL) && collision->OtherCollider == collision->OtherGameObject->Get_Component(L"BodyCollider", ID_ALL))
	{
		_vec3 amountVec = collision->amountVec;
		if (m_pTransform == nullptr) return;

		_float fps60 = Engine::Get_Timer(L"Timer_FPS60");
		const float amount = 20.f;
		switch (collision->CollisionDir)
		{
			/*case DIR_UP:
			m_pTransform->m_vInfo[INFO_POS].y -= amountVec.y;
			break;
			case DIR_DOWN:
			m_pTransform->m_vInfo[INFO_POS].y += amountVec.y;
			break;*/
		case DIR_LEFT:
			collision->OtherGameObject->m_pTransform->m_vInfo[INFO_POS].x -= fps60 * amountVec.x * amount;
			break;
		case DIR_RIGHT:
			collision->OtherGameObject->m_pTransform->m_vInfo[INFO_POS].x += fps60 * amountVec.x * amount;
			break;
		case DIR_FRONT:
			collision->OtherGameObject->m_pTransform->m_vInfo[INFO_POS].z += fps60 * amountVec.z * amount;
			break;
		case DIR_BACK:
			collision->OtherGameObject->m_pTransform->m_vInfo[INFO_POS].z -= fps60 * amountVec.z * amount;
			break;
		default:
			break;
		}

	}
}

HRESULT CSoftPyramid::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CComponent *pComponent;

	pComponent = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"SoftPyramid_Texture", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"SoftPyramid_Texture", pComponent });

	return result;
}

CSoftPyramid * CSoftPyramid::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSoftPyramid* pInstance = new CSoftPyramid(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CSoftPyramid::SetDead(_bool bDead)
{
	__super::SetDead(bDead);
	_vec3 pSpawnPos = m_pTransform->m_vInfo[INFO_POS];
	pSpawnPos.y += 1.f;
	Add_GameObject(CWeaponItem::Create(m_pGraphicDev
		, pSpawnPos
		, FLAMESHOT));

	pSpawnPos.y = 0.1f;
	/*CTile* pTile = CTile::Create(m_pGraphicDev, pSpawnPos, L"FloorCrate_Texture");*/
	//ROOM_MGR->Get_CurRoom()->PushBack_GameObj(pTile);
	//pTile->m_pTransform->m_vScale *= 0.5f;
}

void CSoftPyramid::Free(void)
{
	__super::Free();
}
