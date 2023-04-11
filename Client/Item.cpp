#include "Item.h"
#include "Export_Function.h"
#include "Player.h"

CItem::CItem(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
	Set_LayerID(LAYER_ITEM);
	m_bDrop = false;
	m_bBill = true;
	m_fSpeed = 0.01f;
}

CItem::~CItem()
{

}

_int CItem::Update_GameObject(const _float & fTimeDelta)
{
	Add_RenderGroup(RENDER_ALPHA, this);
	_matrix matView;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	if (m_bBill)
		m_pTransform->Set_Billboard(&matView);
	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);
	return __super::Update_GameObject(fTimeDelta);
}

void CItem::OnCollisionEnter(const Collision * collsion)
{
	__super::OnCollisionEnter(collsion);	
	CPlayer* player = dynamic_cast<CPlayer*>(collsion->OtherGameObject);

	if (player && collsion->MyCollider == Get_Component(L"Collider", ID_ALL))
	{
		SetDead();
	}
}


void CItem::ItemPatrol()
{
	m_pTransform->Set_Pos(m_pTransform->m_vInfo[INFO_POS].x,
		m_fY,
		m_pTransform->m_vInfo[INFO_POS].z);

	m_fY += m_fSpeed;
	if (m_fY >= m_fMaxY || m_fY <= m_fMinY)
	{
		m_fSpeed *= -1.f;
	}
}

void CItem::Free()
{
	Safe_Release(m_pAniCom);
	Safe_Release(m_pTextureCom);
	__super::Free();
}