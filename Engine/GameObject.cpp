#include "stdafx.h"
#include "GameObject.h"
#include "Transform.h"
#include "Export_Function.h"


// 테스트용 주석

// 여기는 안보셔도 됩니다. 굳이 안봐도 돼요.
bool Compare_Component_Priority(pair<const _tchar*, CComponent*>& a, pair<const _tchar*, CComponent*>& b)
{
	return a.second->m_RenderOrder < b.second->m_RenderOrder; // Value로 정렬
}


CGameObject::CGameObject(LPDIRECT3DDEVICE9 pGraphicDev) : 
	m_pGraphicDev(pGraphicDev),
	m_fViewZ(0.f),
	m_bDead(FALSE)
{
	m_pGraphicDev->AddRef();

	m_pTransform = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Transform", this));
	m_uMapComponent[ID_UPDATE].insert({ L"Transform", m_pTransform });
}

CGameObject::~CGameObject()
{
}

CComponent * CGameObject::Get_Component(const _tchar * pComponentTag, COMPONENTID eID)
{
	CComponent*		pComponent = Find_Component(pComponentTag, eID);
	//NULL_CHECK_RETURN(pComponent, nullptr);

	return pComponent;
}

CVIBuffer* CGameObject::Get_VIBuffer()
{
	CVIBuffer* pBuffer = nullptr;
	for (_ulong i = 0; i < ID_END; ++i)
	{
		for (auto& Component : m_uMapComponent[i])
		{
			if (pBuffer = dynamic_cast<CVIBuffer*>(Component.second))
				return pBuffer;
		}
	}
	return nullptr;
}

HRESULT CGameObject::Ready_GameObject(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	// 여기 아래 부분은 굳이 안봐도 됩니다.
	vector <pair<const _tchar*, CComponent*>> VecRender(m_uMapComponent[ID_RENDER].begin(), m_uMapComponent[ID_RENDER].end());
	vector <pair<const _tchar*, CComponent*>> VecAll(m_uMapComponent[ID_ALL].begin(), m_uMapComponent[ID_ALL].end());

	vector <pair<const _tchar*, CComponent*>> sortVec;

	sortVec.insert(sortVec.begin(), VecRender.begin(), VecRender.end());
	sortVec.insert(sortVec.end(), VecAll.begin(), VecAll.end());

	sort(sortVec.begin(), sortVec.end(), Compare_Component_Priority);

	m_RenderComponent = sortVec;

	return S_OK;
}

_int CGameObject::Update_GameObject(const _float & fTimeDelta)
{
	for (auto& iter : m_uMapComponent[ID_UPDATE])
		iter.second->Update_Component(fTimeDelta);

	for (auto& iter : m_uMapComponent[ID_ALL])
		iter.second->Update_Component(fTimeDelta);

	return 0;
}

void CGameObject::LateUpdate_GameObject(void)
{
	for (auto& iter : m_uMapComponent[ID_UPDATE])
		iter.second->LateUpdate_Component();

	for (auto& iter : m_uMapComponent[ID_ALL])
		iter.second->LateUpdate_Component();
}

void CGameObject::Render_GameObject(void)
{
	for (auto& iter : m_RenderComponent)
		iter.second->Render_Component();

	m_pGraphicDev->SetTexture(0, nullptr);
}

void CGameObject::OnCollisionEnter(const Collision * collsion)
{
}

void CGameObject::OnCollisionStay(const Collision * collision)
{
	// 몬스터끼리 서로 밀어내게 하면됨.
	if (collision->MyCollider == Get_Component(L"BodyCollider", ID_ALL) && collision->OtherCollider == collision->OtherGameObject->Get_Component(L"BodyCollider", ID_ALL))
	{
		_vec3 amountVec = collision->amountVec;
		if (m_pTransform == nullptr) return;

		_float fps60 = Engine::Get_Timer(L"Timer_FPS60");

		switch (collision->CollisionDir)
		{
		/*case DIR_UP:
			m_pTransform->m_vInfo[INFO_POS].y -= amountVec.y;
			break;
		case DIR_DOWN:
			m_pTransform->m_vInfo[INFO_POS].y += amountVec.y;
			break;*/
		case DIR_LEFT:
			m_pTransform->m_vInfo[INFO_POS].x += fps60*amountVec.x * 6;
			break;
		case DIR_RIGHT:
			m_pTransform->m_vInfo[INFO_POS].x -= fps60*amountVec.x * 6;
			break;
		case DIR_FRONT:
			m_pTransform->m_vInfo[INFO_POS].z -= fps60*amountVec.z * 6;
			break;
		case DIR_BACK:
			m_pTransform->m_vInfo[INFO_POS].z += fps60*amountVec.z * 6;
			break;
		default:
			break;
		}
			
	}
}

void CGameObject::OnCollisionExit(const Collision * collision)
{
}

void CGameObject::Compute_ViewZ(const _vec3 * pPos)
{
	_matrix		matCamWorld;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matCamWorld);
	D3DXMatrixInverse(&matCamWorld, 0, &matCamWorld);
	
	_vec3	vCamPos;
	memcpy(&vCamPos, &matCamWorld.m[3][0], sizeof(_vec3));

	m_fViewZ = D3DXVec3Length(&(vCamPos - *pPos));
}

void CGameObject::Set_Pos(const _vec3 & pos)
{
	m_pTransform->Set_Pos(pos.x, pos.y, pos.z);
}

void CGameObject::Set_Dir(const _vec3 & dir)
{
	m_pTransform->Set_Dir(dir);
}

void CGameObject::Remove_Render_Component(const _tchar * pComponentTag)
{
	for (auto iter = m_RenderComponent.begin(); iter != m_RenderComponent.end(); ++iter)
	{
		if (0 == lstrcmp(pComponentTag, iter->first))
		{
			m_RenderComponent.erase(iter);
			return;
		}
	}
}

void CGameObject::Add_Render_Component()
{
	vector <pair<const _tchar*, CComponent*>> VecRender(m_uMapComponent[ID_RENDER].begin(), m_uMapComponent[ID_RENDER].end());
	vector <pair<const _tchar*, CComponent*>> VecAll(m_uMapComponent[ID_ALL].begin(), m_uMapComponent[ID_ALL].end());

	vector <pair<const _tchar*, CComponent*>> sortVec;

	sortVec.insert(sortVec.begin(), VecRender.begin(), VecRender.end());
	sortVec.insert(sortVec.end(), VecAll.begin(), VecAll.end());

	sort(sortVec.begin(), sortVec.end(), Compare_Component_Priority);

	m_RenderComponent = sortVec;
}

CComponent * CGameObject::Find_Component(const _tchar * pComponentTag, COMPONENTID eID)
{
	auto	iter = find_if(m_uMapComponent[eID].begin(), m_uMapComponent[eID].end(), CTag_Finder(pComponentTag));

	if (iter == m_uMapComponent[eID].end())
		return nullptr;

	return iter->second;
}


void CGameObject::Free(void)
{
	for (size_t i = 0; i < ID_END; ++i)
	{
		for (auto iter = m_uMapComponent[i].begin(); iter != m_uMapComponent[i].end(); iter++)
		{
			Safe_Release((iter->second));
		}
		m_uMapComponent[i].clear();
	}
	Safe_Release(m_pGraphicDev);
}
