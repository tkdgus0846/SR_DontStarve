#pragma once
#include "ImWindow.h"
#include "ImImage.h"

BEGIN(Engine)
class CGameObject;
END

class CRoomMgr;
class CRoom;
class CImInspector : public CImWindow
{
private:
	explicit CImInspector(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CImInspector();

public:
	virtual HRESULT Ready_ImWindow() override;
	virtual _int	Update(float fTimeDelta) override;

private:
	void Show_RoomInfo();
	void Show_TilePicking();
	void Show_Create_Object();
	void Show_MonsterList();
	void Show_Components();

private:
	CRoom*			m_pCurRoom;
	_vec3			m_vObjectPos;
	CGameObject*	m_pCurTarget;
	vector<pair<const char*, CGameObject*>>	m_vecMonster;
	vector<pair<const char*, CGameObject*>>	m_vecMap;

	ImImage*		m_pMonsterImage;
	ImImage*		m_pMapObjImage;
	ImImage*		m_pTileImage;
	

public:
	static CImInspector* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};