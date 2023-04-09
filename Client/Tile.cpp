#include "stdafx.h"
#include "Tile.h"

#include "Export_Function.h"

CTile::CTile(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
}


CTile::~CTile()
{
}

HRESULT CTile::Ready_GameObject(const _tchar* pTextureName)
{
	m_pTextureName = pTextureName;
	HRESULT result = __super::Ready_GameObject();

	m_pTransform->m_vScale *= VTXITV * 0.5f;
	m_pTransform->Rot_Pitch(90.f, 1);

	return result;
}

_int CTile::Update_GameObject(const _float & fTimeDelta)
{
	__super::Update_GameObject(fTimeDelta);

	__super::Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return 0;
}

void CTile::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CTile::Render_GameObject(void)
{
	__super::Render_GameObject();
}

HRESULT CTile::Add_Component()
{
	CRcTex* pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(pBufferCom, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"RcTex", pBufferCom });

	Change_Texture(m_pTextureName);

	return S_OK;
}

HRESULT CTile::Remove_TextureCom()
{
	for (_uint i = 0; i < ID_END; ++i)
	{
		for (auto iter = m_uMapComponent[i].begin(); iter != m_uMapComponent[i].end(); ++iter)
		{
			if (0 == lstrcmp(iter->first, m_pTextureName))
			{
				Remove_Render_Component(iter->first);
				m_uMapComponent[i].erase(iter);
				Safe_Release(m_pTextureCom);
				m_pTextureName = L"";
				return S_OK;
			}
		}
	}
	return E_FAIL;
}

void CTile::Change_Texture(const _tchar * pTextureName)
{
	Remove_TextureCom();

	m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(pTextureName, this));
	m_pTextureName = pTextureName;
	NULL_CHECK_RETURN(m_pTextureCom);
	m_uMapComponent[ID_RENDER].emplace(m_pTextureName, m_pTextureCom);

	Add_Render_Component();
}

CTile * CTile::Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 vPos,
	const _tchar* pTextureName)
{
	CTile*	pInstance = new CTile(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(pTextureName)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	pInstance->m_pTransform->m_vInfo[INFO_POS] = vPos;

	return pInstance;
}

void CTile::Free(void)
{
	__super::Free();
}

