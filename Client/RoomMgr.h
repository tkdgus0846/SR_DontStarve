#pragma once

#include "Base.h"
#include "Include.h"

BEGIN(Engine)
class CCollider;
class CLayer;
END

class CRoom;

class CRoomMgr : public CBase
{
	DECLARE_SINGLETON(CRoomMgr);
public:
	explicit CRoomMgr();
	~CRoomMgr();

public:
	HRESULT Ready_RoomMgr(LPDIRECT3DDEVICE9	pGraphicDev);

	class CRoom*			Get_CurRoom(const _vec3& vPos);
	void			Set_CurRoom(const _uint iIndex); 
	class CTennel*		Get_Tennel(const _int i) { return m_pTennel[i]; }

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
	class CTennel*		m_pTennel[2];//0 == 진입, 1 == 진출
	LPDIRECT3DDEVICE9	m_pGraphicDev;

public:
	void Free();
};

#define ROOM_MGR CRoomMgr::GetInstance()

