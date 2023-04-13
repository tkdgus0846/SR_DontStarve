#include "NogadaFactory.h"
#include "GameObject.h"
#include "Monster.h"
#include "RoomMgr.h"
#include "Export_Function.h"

#include "Baller.h"
#include "Bub.h"
#include "Guppi.h"
#include "Turret.h"
#include "Walker.h"

IMPLEMENT_SINGLETON(CNogadaFactory)

CNogadaFactory::CNogadaFactory()
{
}

CNogadaFactory::~CNogadaFactory()
{
	Release();
}

HRESULT CNogadaFactory::Ready_CNogadaFactory(LPDIRECT3DDEVICE9 pGraphicDev)
{
	m_pGraphicDev = pGraphicDev;
	m_pGraphicDev->AddRef();

	// Monster
	InsertObj("Baller", CBaller::Create(m_pGraphicDev, _vec3{}));
	InsertObj("Bub", CBub::Create(m_pGraphicDev, _vec3{}));
	InsertObj("Guppi", CGuppi::Create(m_pGraphicDev, _vec3{}));
	InsertObj("Turret", CTurret::Create(m_pGraphicDev, _vec3{}));
	InsertObj("Walker", CWalker::Create(m_pGraphicDev, _vec3{}));


	return S_OK;
}

void CNogadaFactory::Release()
{
	for_each(m_mapTag.begin(), m_mapTag.end(), CDeleteMap());
}

CGameObject * CNogadaFactory::CreateObj(OBJ_TYPE eType, const char* tag, _vec3 vPos)
{
	CGameObject* pGameObject = nullptr;
	

	return pGameObject;
}

CGameObject * CNogadaFactory::Find_Obj(const char * pTag)
{
	auto	iter = find_if(m_mapTag.begin(), m_mapTag.end(), CTag_MyFinder(pTag));

	if (iter == m_mapTag.end())
		return nullptr;

	return iter->second;
}