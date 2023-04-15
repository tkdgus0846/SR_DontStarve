#include "stdafx.h"
#include "Tile.h"
#include "Player.h"
#include "Export_Function.h"

CTile::CTile(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
	, m_eTileType(TILE_DEFAULT)
{
	Set_LayerID(LAYER_TRIGGER);
	Set_ObjTag(L"Tile");


}

CTile::~CTile()
{
}

HRESULT CTile::Ready_GameObject(const _tchar* pTextureName)
{
	//lstrcpy(m_pTextureName, pTextureName);
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

void CTile::CalcColliderSize()
{
	// 타일 콜라이더 크기 조절 분기문(더러움주의)
	if (fabs(this->NormalVectorFromTile().Degree(_vec3::Up())) < 0.1f
		|| fabs(this->NormalVectorFromTile().Degree(-_vec3::Up())) < 0.1f)
		this->GetCollider()->Set_BoundingBox({ 10.f, 1.f, 10.f });
	else if (fabs(this->NormalVectorFromTile().Degree(_vec3::Right())) < 0.1f
		|| fabs(this->NormalVectorFromTile().Degree(-_vec3::Right())) < 0.1f)
		this->GetCollider()->Set_BoundingBox({ 1.f, 10.f, 10.f });
	else
		this->GetCollider()->Set_BoundingBox({ 10.f, 10.f, 1.f });
}

void CTile::OnCollisionStay(const Collision * collision)
{
	if (collision->OtherCollider == collision->OtherGameObject->Get_Component(L"BodyCollider", ID_ALL))
	{
		switch (m_eTileType)
		{
		case TILE_BELT:
			collision->OtherGameObject
				->m_pTransform->Move_WalkWithVec(m_pTransform->m_vInfo[INFO_UP], 10.f, 0.016f);
			break;
		case TILE_BLOOD:
			break;
		case TILE_ELECTRIC:
			break;
		case TILE_LAVA:
			break;
		case TILE_OIL:
			break;
		case TILE_QUICKSAND:
			break;
		case TILE_SWAMP:
			break;
		case TILE_ICE:
			break;
		case TILE_SAND:
			break;
		case TILE_GRASS:
			break;
		case TILE_DEFAULT:
			break;
		case TILE_SNOW:
			break;
		case TILE_END:
			break;
		default:
			break;
		}
	}	
}

_vec3 CTile::NormalVectorFromTile()
{
	CRcTex* pBufferCom = dynamic_cast<CRcTex*>(Get_Component(L"RcTex", ID_RENDER));
	NULL_CHECK(pBufferCom);
	Triangle tri;

	VTXTEX*		pVertex = nullptr;
	pBufferCom->GetVertexBuffer()->Lock(0, 0, (void**)&pVertex, 0);

	tri.v[0] = pVertex[0].vPos;
	tri.v[1] = pVertex[1].vPos;
	tri.v[2] = pVertex[2].vPos;

	pBufferCom->GetVertexBuffer()->Unlock();

	tri.v[0].TransformCoord(&m_pTransform->m_matWorld);
	tri.v[1].TransformCoord(&m_pTransform->m_matWorld);
	tri.v[2].TransformCoord(&m_pTransform->m_matWorld);

	return tri.Normal();
}

HRESULT CTile::Add_Component()
{
	CRcTex* pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(pBufferCom, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", pBufferCom });

	m_pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Collider", this, COL_ENVIRONMENT));
	NULL_CHECK_RETURN(m_pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Collider", m_pCollider });

	m_pAnimation = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(m_pAnimation, E_FAIL);
	//m_uMapComponent[ID_ALL].insert({ L"Animation", m_pAnimation });

	Change_Texture(m_pTextureName);

	return S_OK;
}

HRESULT CTile::Remove_TextureCom()
{
	for (_uint i = 0; i < ID_END; ++i)
	{
		for (auto iter = m_uMapComponent[i].begin(); iter != m_uMapComponent[i].end(); ++iter)
		{
			//if (0 == lstrcmp(iter->first, m_pTextureName))
			if (iter->first == m_pTextureName)
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

void CTile::Set_TileType(const _tchar * pTextureName)
{
	if (0 == lstrcmp(pTextureName, L"FloorLava"))
		m_eTileType = TILE_LAVA;
	else if (0 == lstrcmp(pTextureName, L"FloorIce"))
		m_eTileType = TILE_ICE;
	else if (0 == lstrcmp(pTextureName, L"FloorSand #421867"))
		m_eTileType = TILE_SAND;
	else if (0 == lstrcmp(pTextureName, L"FloorGrass #421873"))
		m_eTileType = TILE_GRASS;
	else if (0 == lstrcmp(pTextureName, L"FloorElectric"))
		m_eTileType = TILE_ELECTRIC;
	else if (0 == lstrcmp(pTextureName, L"FloorSwamp"))
		m_eTileType = TILE_SWAMP;
	else if (0 == lstrcmp(pTextureName, L"FloorSnow"))
		m_eTileType = TILE_SNOW;
	else if (0 == lstrcmp(pTextureName, L"FloorBelt"))
		m_eTileType = TILE_BELT;
	else
		m_eTileType = TILE_DEFAULT;
}

void CTile::Change_Texture(const _tchar * pTextureName)
{
	Remove_TextureCom();
	
	m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(pTextureName, this));
	/*_tchar tmp[32];
	lstrcpy(tmp, pTextureName);
	lstrcpy(m_pTextureName, tmp);*/
	m_pTextureName = pTextureName;
	NULL_CHECK_RETURN(m_pTextureCom);
	m_uMapComponent[ID_RENDER].emplace(m_pTextureName, m_pTextureCom);
	Set_TileType(pTextureName);

	Add_Render_Component();

	m_pAnimation->BindAnimation(ANIM_IDLE, m_pTextureCom);
	m_pAnimation->SelectState(ANIM_IDLE);
	m_uMapComponent[ID_ALL].insert({ L"Animation", m_pAnimation });
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
	pInstance->Update_GameObject(1/60.f);
	pInstance->CalcColliderSize();
	return pInstance;
}

void CTile::Free(void)
{
	__super::Free();
}

