#pragma once

#include "GameObject.h"

BEGIN(Engine)
class CTexture;
class CCollider;
END

class CRoom;
class CTennel;
class CDoor : public CGameObject
{
private:
	explicit CDoor(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CDoor();

public:
	virtual HRESULT Ready_GameObject(DOOR_DIR eDir, CRoom* pRoom);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	virtual void OnCollisionEnter(const class Collision* collsion);
	CRoom* Get_Room() { return m_pRoom; }
	DOOR_DIR Get_Door_Dir() { return m_eDir; }

private:
	virtual HRESULT Add_Component() override;
	void Set_Door_State();

private:
	CRoom*					m_pRoom;	// ���� ���� �����ִ� ���� ������
	CTennel*				m_pInTennel;	// �������� �ͳ�������
	CTennel*				m_pOutTennel;	// �������� �ͳ�������
	Engine::CTexture*		m_pTextureCom;
	Engine::CCollider*		m_pCollider;

	DOOR_DIR				m_eDir;		// �� �ȿ��� ���� ��ġ(��������)

public:
	static CDoor*		Create(LPDIRECT3DDEVICE9 pGraphicDev, DOOR_DIR eDir, CRoom* pRoom);

private:
	virtual void Free(void) override;
};

