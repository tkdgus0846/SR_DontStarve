#pragma once
#include "GameObject.h"
#include "Room.h"

BEGIN(Engine)
class CTexture;
END

class CRoom;
class CTennel;

class CRoomMgr
{
	DECLARE_SINGLETON(CRoomMgr);
public:
	CRoomMgr();
	virtual ~CRoomMgr();

public:
	HRESULT Ready_RoomMgr(LPDIRECT3DDEVICE9	pGraphicDev);

	CRoom*			Get_CurRoom(const _vec3& vPos);
	void			Set_CurRoom(const _uint iIndex) { m_pCurRoom = m_arrRoom[iIndex]; }
	CTennel*		Get_Tennel() { return m_pTennel[0]; }

	_bool WriteMapFile(HANDLE hFile, DWORD& dwByte);
	_bool ReadMapFile(HANDLE hFile, DWORD& dwByte);

	vector<CLayer*>* Get_CurLayerVec() { return m_pCurRoom->GetLayerVec(); }
	list<CCollider*>* Get_CurColliderList(_int iIndex)
	{
		return m_pCurRoom->GetColliderList(iIndex);
	}

private:
	void			Create_Default_Room();
			
private:
	CRoom*				m_pCurRoom;
	array<CRoom*, 25>	m_arrRoom;
	CTennel*			m_pTennel[2];//0 == ����, 1 == ����
	LPDIRECT3DDEVICE9	m_pGraphicDev;

private:
	void Free();
};

#define ROOM_MGR CRoomMgr::GetInstance()

