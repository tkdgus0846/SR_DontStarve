#include "Door.h"

#include "Export_Function.h"

#include "RoomMgr.h"


CDoor::CDoor(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev), m_pRoom(nullptr)
	, m_pTennel(nullptr)
{
}

CDoor::~CDoor()
{
}

HRESULT CDoor::Ready_GameObject(const _vec3& vPos, _bool IsRot, const CRoom* pRoom)
{
	HRESULT Result = __super::Ready_GameObject();

	m_pRoom = pRoom;
	m_pTennel = ROOM_MGR->Get_Tennel();

	m_pTransform->m_vInfo[INFO_POS] = vPos;
	m_pTransform->m_vScale = { 3.f, 5.f, 1.f };

	if (IsRot)
		m_pTransform->Rot_Yaw(90.f, 1.f);

	return Result;
}

_int CDoor::Update_GameObject(const _float & fTimeDelta)
{
	
	__super::Update_GameObject(fTimeDelta);

	__super::Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	Add_RenderGroup(RENDER_ALPHA, this);

	return 0;
}

void CDoor::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CDoor::Render_GameObject(void)
{
	__super::Render_GameObject();
}

void CDoor::OnCollisionEnter(const Collision * collsion)
{
	collsion->OtherGameObject;
}

HRESULT CDoor::Add_Component()
{
	CRcTex* pBufferCom = dynamic_cast<CRcTex*>(Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(pBufferCom, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"RcTex", pBufferCom });

	m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Dock_Texture", this));
	NULL_CHECK_RETURN(m_pTextureCom);
	m_uMapComponent[ID_RENDER].emplace(L"Dock_Texture", m_pTextureCom);

	m_pCollider = dynamic_cast<CCollider*>(Clone_Proto(L"Collider", this, COL_TRIGGER));
	NULL_CHECK_RETURN(m_pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Collider", m_pCollider });
	m_pCollider->Set_BoundingBox({ 1.f, 4.f, 1.f });
	
	return S_OK;
}

CDoor * CDoor::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos, _bool IsRot, const CRoom* pRoom)
{
	CDoor* pInstance = new CDoor(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(vPos, IsRot, pRoom)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CDoor::Free(void)
{
	__super::Free();
}
