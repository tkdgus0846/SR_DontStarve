#include "Factory.h"

CFactory::CFactory()
{
}

CFactory::~CFactory()
{
}

void CFactory::Register(const wstring & objectType, CreateObjectFunc createFunc)
{
	m_creationMap[objectType] = createFunc;
}

HRESULT CFactory::Ready_TileFactory(LPDIRECT3DDEVICE9 pGraphicDev)
{
	m_pGraphicDev = pGraphicDev;
	m_pGraphicDev->AddRef();
	return S_OK;
}

void CFactory::Release()
{
	if(m_pGraphicDev)
		m_pGraphicDev->Release();
}

CGameObject * CFactory::CreateObject(const wstring & objectType)
{
	auto it = m_creationMap.find(objectType);
	if (it != m_creationMap.end())
	{
		return it->second(m_pGraphicDev);
	}
	return nullptr;
}