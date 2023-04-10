#include "stdafx.h"
#include "Tile.h"

#include "Export_Function.h"

CTile::CTile(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
	, m_iTileOption(0)
{
}

CTile::~CTile()
{
}

HRESULT CTile::Ready_GameObject(const _tchar* pTextureName)
{
	lstrcpy(m_pTextureName, pTextureName);
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

void CTile::WriteTextureName(HANDLE hFile, DWORD & dwByte)
{
	WriteFile(hFile, m_pTextureName, sizeof(_tchar) * 64, &dwByte, nullptr);
}

void CTile::ReadTextureName(HANDLE hFile, DWORD & dwByte)
{
	_tchar pTextureName[64];
	ReadFile(hFile, pTextureName, sizeof(_tchar) * 64, &dwByte, nullptr);
	const _tchar* tmp = const_cast<const _tchar*>(pTextureName);
	Change_Texture(tmp);
}

HRESULT CTile::Add_Component()
{
	CRcTex* pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(pBufferCom, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"RcTex", pBufferCom });

	m_pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", this, COL_ENVIRONMENT));
	NULL_CHECK_RETURN(m_pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"TileCollider", m_pCollider });

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
				lstrcpy(m_pTextureName, L"");
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
	_tchar tmp[32];
	lstrcpy(tmp, pTextureName);
	lstrcpy(m_pTextureName, tmp);
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

