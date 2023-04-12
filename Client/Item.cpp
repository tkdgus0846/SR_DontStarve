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
	fTime = 2.0f;

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
	//ItemDrop(fTimeDelta);
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

void CItem::OnCollisionStay(const Collision * collision)
{
	__super::OnCollisionStay(collision);
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

void CItem::ItemMagnetic(CPlayer* pPlayer)
{
	_vec3 pPlayerInfo;
	pPlayer->m_pTransform->Get_Info(INFO_POS, &pPlayerInfo);
	_vec3 vDir = pPlayerInfo - m_pTransform->m_vInfo[INFO_POS];
	D3DXVec3Normalize(&vDir, &vDir);
	m_pTransform->m_vInfo[INFO_POS] +=  vDir * 0.5f;
}

void CItem::ItemDrop(const _float& fTimeDelta)
{
	if (m_bDrop == false)
	{
		float v0, theta, t, g; // 초기 속도, 발사 각도, 시간, 중력 가속도 변수

		v0 = 10.0f;
		theta = D3DXToRadian(45.f);
		g = 9.8f;

		float v0x = v0 * cos(theta); // x 방향 초기 속도
		float v0y = v0 * sin(theta); // y 방향 초기 속도

		m_pTransform->m_vInfo[INFO_POS].y = (v0y * fTime) - (0.5f * g * fTime * fTime); // y 위치 계산 (중력 가속도에 음수를 곱해야 함, 시간의 제곱에 0.5를 곱해야 함)

		fTime += 0.05f;

		if (fTime > 3.f)
		{
			fTime = 0.f;
		}
/*
		if (m_pTransform->m_vInfo[INFO_POS].y < m_fY + 0.1f && m_pTransform->m_vInfo[INFO_POS].y > m_fY - 0.1f)
		{
			m_bDrop = true;
		}
*/
		cout << m_pTransform->m_vInfo[INFO_POS].y << endl;
	}
}

void CItem::Free()
{
	Safe_Release(m_pAniCom);
	Safe_Release(m_pTextureCom);
	__super::Free();
}