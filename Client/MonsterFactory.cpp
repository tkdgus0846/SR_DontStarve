#include "MonsterFactory.h"
#include "WormBody.h"
#include "WormHead.h"
#include "WormTail.h"
#include "NubBoss.h"
#include "WalkerBoss.h"
#include "Baller.h"
#include "Bub.h"
#include "Cryder.h"
#include "Guppi.h"
#include "Rub.h"
#include "Turret.h"
#include "Walker.h"
#include "ShopNpc.h"

IMPLEMENT_SINGLETON(CMonsterFactory)

CMonsterFactory::CMonsterFactory()
{
}


CMonsterFactory::~CMonsterFactory()
{
	Release();
}

HRESULT CMonsterFactory::Ready_Factory(LPDIRECT3DDEVICE9 pGraphicDev)
{
	HRESULT hResult = __super::Ready_Factory(pGraphicDev);

	Register(CWormHead::Tag(),	&CWormHead::Create);
	//Register(CWormBody::Tag(),	&CWormBody::Create);
	//Register(CWormTail::Tag(),	&CWormTail::Create);
	Register(CNubBoss::Tag(),	&CNubBoss::Create);
	Register(CWalkerBoss::Tag(),&CWalkerBoss::Create);
	Register(CBaller::Tag(),	&CBaller::Create);
	Register(CBub::Tag(),		&CBub::Create);
	Register(CCryder::Tag(),	&CCryder::Create);
	Register(CGuppi::Tag(),		&CGuppi::Create);
	Register(CRub::Tag(),		&CRub::Create);
	Register(CTurret::Tag(),	&CTurret::Create);
	Register(CWalker::Tag(),	&CWalker::Create);
	Register(CShopNpc::Tag(),	&CShopNpc::Create);

	ExtractTextureKey();

	return hResult;
}
