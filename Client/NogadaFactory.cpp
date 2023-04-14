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
#include "SoftPyramid.h"
#include "HardPyramid.h"
#include "Slider.h"

IMPLEMENT_SINGLETON(CNogadaFactory)
// 새로운 클래스 추가 할때마다 Push_Back함수로 새로 추가하고,
// CreateObj 함수를 수정하면 됨.
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
	Push_Back(OBJ_MONSTER, "Baller", CBaller::Create(m_pGraphicDev, _vec3{}));
	Push_Back(OBJ_MONSTER, "Bub", CBub::Create(m_pGraphicDev, _vec3{}));
	Push_Back(OBJ_MONSTER, "Guppi", CGuppi::Create(m_pGraphicDev, _vec3{}));
	Push_Back(OBJ_MONSTER, "Turret", CTurret::Create(m_pGraphicDev, _vec3{}));
	Push_Back(OBJ_MONSTER, "Walker", CWalker::Create(m_pGraphicDev, _vec3{}));

	// MapObject
	Push_Back(OBJ_MAPOBJ, "SoftPyramid", CSoftPyramid::Create(m_pGraphicDev));
	Push_Back(OBJ_MAPOBJ, "HardPyramid", CHardPyramid::Create(m_pGraphicDev));
	Push_Back(OBJ_MAPOBJ, "Slider", CSlider::Create(m_pGraphicDev));

	return S_OK;
}

void CNogadaFactory::Release()
{
	for (_int i = 0; i < OBJ_END; ++i)
	{
		for_each(m_vecObj[i].begin(), m_vecObj[i].end(), CDeleteObj());
		m_vecObj[i].clear();
	}
}

CGameObject * CNogadaFactory::GetGameObj(const char * tag)
{
	CGameObject* pObj = Find_Obj(tag);

	return pObj;
}

CGameObject * CNogadaFactory::CreateObj(const char * tag)
{
	// Monster
	if (0 == strcmp(tag, "Baller"))
		return CBaller::Create(m_pGraphicDev, _vec3{0.f, 0.f, 0.f});
	else if (0 == strcmp(tag, "Bub"))
		return CBub::Create(m_pGraphicDev, _vec3{ 0.f, 0.f, 0.f });
	else if (0 == strcmp(tag, "Guppi"))
		return CGuppi::Create(m_pGraphicDev, _vec3{ 0.f, 0.f, 0.f });
	else if (0 == strcmp(tag, "Turret"))
		return CTurret::Create(m_pGraphicDev, _vec3{ 0.f, 0.f, 0.f });
	else if (0 == strcmp(tag, "Walker"))
		return CWalker::Create(m_pGraphicDev, _vec3{ 0.f, 0.f, 0.f });
	// Map
	else if (0 == strcmp(tag, "SoftPyramid"))
		return CSoftPyramid::Create(m_pGraphicDev);
	else if (0 == strcmp(tag, "HardPyramid"))
		return CHardPyramid::Create(m_pGraphicDev);
	else if (0 == strcmp(tag, "Slider"))
		return CSlider::Create(m_pGraphicDev);

	return nullptr;
}

CGameObject * CNogadaFactory::Find_Obj(const char* tag)
{
	CGameObject* pGameObject = nullptr;
	for (_int i = 0; i < OBJ_END; ++i)
	{
		for (_int j = 0; j < m_vecTag[i].size(); ++j)
		{
			if (0 == strcmp(m_vecTag[i][j], tag))
			{
				return m_vecObj[i][j];
			}
		}
	}
	
	return pGameObject;
}

CTexture * CNogadaFactory::GetTexture(const char * tag)
{
	CGameObject* pObj = GetGameObj(tag);
	if (!pObj)
		return nullptr;

	CTexture* pTexture = pObj->Get_Texture();
	return pTexture;
}
