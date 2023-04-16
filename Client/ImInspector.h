#pragma once
#include "ImWindow.h"
#include "ImImage.h"

BEGIN(Engine)
class CGameObject;
END

class CRoomMgr;
class CRoom;
class CEditCamera;

class CImInspector : public CImWindow
{
private:
	explicit CImInspector(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CImInspector();

public:
	virtual HRESULT Ready_ImWindow() override;
	virtual _int	Update(float fTimeDelta) override;

	const string& Get_CurTileItem() const {
		return m_CurTileItem;
	}

private:
	void Show_RoomInfo();
	void Show_TilePicking();
	void Show_Create_Object();
	void Show_MonsterList();
	void Show_Components();

	void IsPickMode(ImImage* pImage, PICK_TYPE eType);
private:
	CRoom*			m_pCurRoom;
	_vec3			m_vObjectPos;
	CGameObject*	m_pCurTarget;

	string			m_CurTileItem = "a";
	string			m_CurMonsterItem = "a";
	string			m_CurMapObjItem = "a";

	vector<pair<const char*, CGameObject*>>	m_vecMonster;
	vector<pair<const char*, CGameObject*>>	m_vecMap;

	ImImage*		m_pMonsterImage;
	ImImage*		m_pMapObjImage;
	ImImage*		m_pTileImage;
	
	CEditCamera*	m_pCamera;

public:
	static CImInspector* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};