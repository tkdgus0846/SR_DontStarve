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
	HRESULT Ready_GameObject(void);

	CRoom*			Get_CurRoom(const _vec3& vPos);
	void			Set_CurRoom(const _uint iIndex) { m_pCurRoom = m_arrRoom[iIndex]; }
	CTennel*		Get_Tennel() { return m_pTennel[0]; }

	_bool WriteMapFile(HANDLE hFile, DWORD& dwByte);
	_bool ReadMapFile(HANDLE hFile, DWORD& dwByte);

private:
	void			Create_Default_Room();
			
private:
	CRoom*				m_pCurRoom;
	array<CRoom*, 25>	m_arrRoom;
	CTennel*			m_pTennel[2];//0 == 진입, 1 == 진출
	LPDIRECT3DDEVICE9	m_pGraphicDev;

private:
	void Free();
};

