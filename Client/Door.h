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
	virtual HRESULT Ready_GameObject(const _vec3& vPos, _bool IsRot, const CRoom* pRoom);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	virtual void OnCollisionEnter(const class Collision* collsion);

private:
	virtual HRESULT Add_Component() override;

private:
	const CRoom*			m_pRoom;	// ���� ���� �����ִ� ���� ������
	CTennel*				m_pTennel;	// �������� �ͳ�������
	Engine::CTexture*		m_pTextureCom;
	Engine::CCollider*		m_pCollider;

public:
	static CDoor*		Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos, _bool IsRot, const CRoom* pRoom);

private:
	virtual void Free(void) override;
};

