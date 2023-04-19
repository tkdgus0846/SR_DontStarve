#include "WormTail.h"

#include "WormHead.h"
#include "WormBody.h"
#include "Export_Function.h"

CWormTail::CWormTail(LPDIRECT3DDEVICE9 pGraphicDev)
	:CMonster(pGraphicDev), m_pFrontBody(nullptr),
	m_bMove(false), m_pHead(nullptr)
{
	ZeroMemory(m_vDest, sizeof(_vec3));
	Set_ObjTag(Tag());
}

CWormTail::~CWormTail()
{
}

HRESULT CWormTail::Ready_GameObject(const _vec3 & vPos)
{
	m_fSpeed = 9.f;
	m_iAttack = 1;
	m_iHp = 20;
	m_iMaxHp = 20;

	m_pTransform->m_vScale = { 1.5f, 1.5f, 1.5f };
	m_pTransform->m_vInfo[INFO_POS] = vPos;
	m_pTransform->Set_MoveType(CTransform::AIRCRAFT);

	m_pTransform->Set_BillMode(true);

	HRESULT result = __super::Ready_GameObject();

	return result;
}

_int CWormTail::Update_GameObject(const _float & fTimeDelta)
{
	__super::Update_GameObject(fTimeDelta);

	if (GetDead())
	{
		if (m_pFrontBody)
			m_pFrontBody->Chain_Back(nullptr);

		return OBJ_DEAD;
	}

	if (m_pHead)
	{
		m_fSpeed = m_pHead->Get_Speed();
		if (m_pHead->Get_Move() != m_bMove)
			m_bMove = m_pHead->Get_Move();
	}

	if (m_pFrontBody)
	{
		m_fSpeed = m_pFrontBody->Get_Speed();
		if (m_pFrontBody->Get_Move() != m_bMove)
			m_bMove = m_pFrontBody->Get_Move();
	}

	if (m_bMove)
		Move(fTimeDelta);

	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return 0;
}

void CWormTail::LateUpdate_GameObject(void)
{
	if (GetDead())
		return;

	if (Get_Player() == nullptr) return;

	m_pTransform->Set_Scale({ 1.5f, 1.5f, 1.5f });

	_vec3 vPos = Get_Player()->m_pTransform->m_vInfo[INFO_POS];
	_vec3 vDir = vPos - m_pTransform->m_vInfo[INFO_POS];
	vDir.Normalize();

	_float fAngleRight = vDir.Degree(m_pTransform->m_vInfo[INFO_RIGHT]);
	_float fAngleUp = vDir.Degree(m_pTransform->m_vInfo[INFO_UP]);
	_float fAngleLook = vDir.Degree(m_pTransform->m_vInfo[INFO_LOOK]);

	if (isnan(fAngleLook))
		return;

	if (fAngleRight < 45.f)
		m_pAnimation->SelectState(ANIM_SIDE);
	else if (fAngleUp < 45.f)
		m_pAnimation->SelectState(ANIM_TOP);
	else if (fAngleLook < 45.f)
		m_pAnimation->SelectState(ANIM_FACE);

	else if (fAngleRight > 135.f)
	{
		m_pTransform->Set_Scale({ -1.5f, 1.5f, 1.5f });
		m_pAnimation->SelectState(ANIM_SIDE);
	}

	else if (fAngleLook > 135.f)
		m_pAnimation->SelectState(ANIM_BACK);

	else if (fAngleUp < 135.f)
	{
		m_pTransform->Set_Scale({ -1.5f, 1.5f, 1.5f });
		m_pAnimation->SelectState(ANIM_TOP);
	}
	else
		m_pAnimation->SelectState(ANIM_FACE);

	__super::LateUpdate_GameObject();
}

void CWormTail::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	if (GetDead())
		return;
	__super::Render_GameObject();
}

HRESULT CWormTail::Add_Component()
{
	m_pAnimation = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(m_pAnimation, E_FAIL);
	m_uMapComponent[ID_ALL].emplace(L"Animation", m_pAnimation);

	CTexture* pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_WormBoss_Tail_Side_Texture", this));
	NULL_CHECK_RETURN(pTexture, E_FAIL);
	m_uMapComponent[ID_STATIC].emplace(L"Monster_WormBoss_Tail_Side_Texture", pTexture);
	m_pAnimation->BindAnimation(ANIM_SIDE, pTexture, 0.05f);

	pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_WormBoss_Tail_Top_Texture", this));
	NULL_CHECK_RETURN(pTexture, E_FAIL);
	m_uMapComponent[ID_STATIC].emplace(L"Monster_WormBoss_Tail_Top_Texture", pTexture);
	m_pAnimation->BindAnimation(ANIM_TOP, pTexture, 0.05f);

	pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_WormBoss_Drill_Back_Texture", this));
	NULL_CHECK_RETURN(pTexture, E_FAIL);
	m_uMapComponent[ID_STATIC].emplace(L"Monster_WormBoss_Body_Face_Texture", pTexture);
	m_pAnimation->BindAnimation(ANIM_FACE, pTexture, 0.05f);

	pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_WormBoss_Tail_Back_Texture", this));
	NULL_CHECK_RETURN(pTexture, E_FAIL);
	m_uMapComponent[ID_STATIC].emplace(L"Monster_WormBoss_Body_Back_Texture", pTexture);
	m_pAnimation->BindAnimation(ANIM_BACK, pTexture, 0.05f);

	m_pAnimation->SelectState(ANIM_FACE);

	CRcTex* pBufferCom1 = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(pBufferCom1, E_FAIL);
	m_uMapComponent[ID_RENDER].emplace(L"RcTex", pBufferCom1);

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_ENEMY));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].emplace(L"BodyCollider", pCollider);
	pCollider->Set_BoundingBox({ 1.8f, 1.8f, 1.8f });

	pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Range", this, COL_DETECTION));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].emplace(L"Range", pCollider);
	pCollider->Set_BoundingBox({ 1.f, 1.f, 1.f });
}

void CWormTail::Move(const _float & fTimeDelta)
{
	_vec3 vPos = m_pTransform->m_vInfo[INFO_POS];
	_vec3 vDir = m_vDest - vPos;
	_float fLength = 0.f;

	if (m_pHead)
	{
		fLength = _vec3(m_pHead->m_pTransform->m_vInfo[INFO_POS] - m_pTransform->m_vInfo[INFO_POS]).Length();
		if (vDir.Length() < 0.1f)
			m_vDest = m_pHead->m_pTransform->m_vInfo[INFO_POS];
	}
	else
	{
		fLength = _vec3(m_pFrontBody->m_pTransform->m_vInfo[INFO_POS] - m_pTransform->m_vInfo[INFO_POS]).Length();
		if (vDir.Length() < 0.1f)
			m_vDest = m_pFrontBody->m_pTransform->m_vInfo[INFO_POS];
	}
	m_pTransform->Set_Target(m_vDest);

	vDir = m_pTransform->m_vInfo[INFO_LOOK];

	vDir.Normalize();
	_vec3 vDirXZ = { vDir.x, 0.f, vDir.z };
	vDirXZ.Normalize();
	_float fAngle = vDir.Degree(_vec3(vDirXZ.x, 0.f, vDirXZ.z));

	if (isnan(fAngle))
		fAngle = 0.f;

	_vec3 vAxis = Get_Player()->m_pTransform->m_vInfo[INFO_POS] - m_pTransform->m_vInfo[INFO_POS];

	m_pTransform->Rot_Bill(fAngle);

	if (fLength < 2.f)
		m_pTransform->Move_Walk(0.1f, fTimeDelta);
	else if (fLength > 3.5f)
		m_pTransform->Move_Walk(m_fSpeed * 1.5f, fTimeDelta);
	else
		m_pTransform->Move_Walk(m_fSpeed, fTimeDelta);
}

CWormTail * CWormTail::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3 & vPos)
{
	CWormTail* pInstance = new CWormTail(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(vPos)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

CGameObject * CWormTail::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CWormTail* pInstance = new CWormTail(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject({})))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CWormTail::Free(void)
{
	__super::Free();
}
