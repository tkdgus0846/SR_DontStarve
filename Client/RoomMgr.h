#pragma once

#include "Base.h"
#include "Include.h"
#include "Room.h"
BEGIN(Engine)
class CCollider;
class CLayer;
END

class CRoomMgr : public CBase
{
	DECLARE_SINGLETON(CRoomMgr);

public:
	explicit CRoomMgr();
	~CRoomMgr();

public:
	HRESULT Ready_RoomMgr(LPDIRECT3DDEVICE9	pGraphicDev);

	class CRoom*		Get_CurRoom() { return m_pCurRoom; }
	void				Set_CurRoom(const _uint iIndex);

	class CTennel*		Get_Tennel(const _int i) { return m_pTennel[i]; }
	void Set_Tennel(class CTennel* tennel, _int iIndex);

	_bool WriteMapFile(HANDLE hFile, DWORD& dwByte);
	_bool ReadMapFile(HANDLE hFile, DWORD& dwByte);

	vector<CLayer*>* Get_CurLayerVec();
	list<CCollider*>* Get_CurColliderList(_int iIndex);
	CRoom* Get_Room(const _int iIndex) { return m_arrRoom[iIndex]; }

private:
	void			Create_Default_Room();
			
private:
	class CRoom*		m_pCurRoom;
	array<CRoom*, 25>	m_arrRoom;

	class CTennel*		m_pTennel[2];	

	LPDIRECT3DDEVICE9	m_pGraphicDev;

public:
	void Free();
};

#define ROOM_MGR CRoomMgr::GetInstance()

