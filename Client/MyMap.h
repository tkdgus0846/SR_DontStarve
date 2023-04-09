#pragma once
#include "GameObject.h"

BEGIN(Engine)
class CTexture;
END

class CRoom;
class CTennel;
class CMyMap : public CGameObject
{
private:
	explicit CMyMap(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CMyMap();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	CRoom*			Get_CurRoom(const _vec3& vPos);

	_bool WriteMapFile(HANDLE hFile, DWORD& dwByte);
	_bool ReadMapFile(HANDLE hFile, DWORD& dwByte);

private:
	virtual HRESULT Add_Component() override;
	void			Create_Default_Room();
			
private:
	array<CRoom*, 25>	m_arrRoom;
	CTennel*			m_pTennel[2];

public:
	static CMyMap* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;
};

