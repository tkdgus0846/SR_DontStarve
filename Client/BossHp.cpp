#include "BossHp.h"
#include "Export_Function.h"
#include "Creature.h"

CBossHp::CBossHp(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev)
{
	Set_ObjTag(L"BossHp");
}

CBossHp::~CBossHp()
{
}

HRESULT CBossHp::Add_Component()
{
	m_dRcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex_Dynamic", this));
	NULL_CHECK_RETURN(m_dRcTex, E_FAIL);

	m_sRcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(m_sRcTex, E_FAIL);

	CTexture* Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"BossHpBar_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_arrMap[BOSS_MAP_HP] = Texture;

	Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"BossHpGuage_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_arrMap[BOSS_MAP_GUAGE] = Texture;

	Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Num_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_arrMap[BOSS_MAP_FONT] = Texture;

	return S_OK;
}

HRESULT CBossHp::Ready_GameObject(void)
{

	__super::Ready_GameObject();

	return S_OK;
}

_int CBossHp::Update_GameObject(const _float & fTimeDelta)
{
	if (Get_GameObject(LAYER_MONSTER, L"WalkerBoss") == nullptr)
		return OBJ_NOEVENT;
	else
	{
		pGameObject = Get_GameObject(LAYER_MONSTER, L"WalkerBoss");
	}
	Engine::Add_RenderGroup(RENDER_ALPHA_UI, this);

	__super::Update_GameObject(fTimeDelta);

	return 0;
}

void CBossHp::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CBossHp::Render_GameObject(void)
{
	for (size_t i = 0; i < BOSS_UI_END; i++)
	{
		switch (i)
		{
		case BOSS_UI_B:
			Set_ViewMatrix_UI(-45.f + i * 30, 270.f);
			dynamic_cast<CTexture*>(m_arrMap[BOSS_MAP_FONT])->Render_Texture(FONT::B);
			break;
		case BOSS_UI_O:
			Set_ViewMatrix_UI(-45.f + i * 30, 270.f);
			dynamic_cast<CTexture*>(m_arrMap[BOSS_MAP_FONT])->Render_Texture(FONT::O);
			break;
		case BOSS_UI_S:
			Set_ViewMatrix_UI(-45.f + i * 30, 270.f);
			dynamic_cast<CTexture*>(m_arrMap[BOSS_MAP_FONT])->Render_Texture(FONT::S);
			break;
		case BOSS_UI_S2:
			Set_ViewMatrix_UI(-45.f + i * 30, 270.f);
			dynamic_cast<CTexture*>(m_arrMap[BOSS_MAP_FONT])->Render_Texture(FONT::S);
			break;
		case BOSS_UI_HP:
			Set_ViewMatrix_UI(0.f, 200.f, 150.f, 30.f);
			dynamic_cast<CTexture*>(m_arrMap[BOSS_MAP_HP])->Render_Texture();
			break;
		case BOSS_UI_GUAGE:
			_float MaxHp = dynamic_cast<CCreature*>(pGameObject)->Get_MaxHP();
			_float CurHp = dynamic_cast<CCreature*>(pGameObject)->Get_HP();
			m_CurHp = CurHp / MaxHp;
			m_dRcTex->Edit_VB(m_CurHp);
			Set_ViewMatrix_UI(0.f, 200.f, 146.f, 26.f);
			dynamic_cast<CTexture*>(m_arrMap[BOSS_MAP_GUAGE])->Render_Texture();
			m_dRcTex->Render_Component();
			continue;
		}
		m_sRcTex->Render_Component();
	}
	__super::Render_GameObject();
}

void CBossHp::Set_ViewMatrix_UI()
{
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);

	_matrix matTrans;
	D3DXMatrixScaling(&matView, 151.f, 33.f, 1.f);
	D3DXMatrixTranslation(&matTrans, 100.f, 100.f, 0.f);
	D3DXMatrixMultiply(&matView, &matView, &matTrans);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
}

void CBossHp::Set_ViewMatrix_UI(_float posX, _float posY)
{
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);

	_matrix matTrans;
	D3DXMatrixScaling(&matView, 32.f, 32.f, 0.f);
	matTrans.Translation(posX, posY, 0.f);
	D3DXMatrixMultiply(&matView, &matView, &matTrans);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
}

void CBossHp::Set_ViewMatrix_UI(_float posX, _float posY, _float scaleX, _float scaleY)
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

CBossHp * CBossHp::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBossHp* pInstance = new CBossHp(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CBossHp::Free(void)
{
	Safe_Release(m_sRcTex);
	Safe_Release(m_dRcTex);

	auto iter = m_arrMap.begin();
	for (; iter < m_arrMap.end(); iter++)
	{
		Safe_Release(*iter);
	}
	__super::Free();
}
