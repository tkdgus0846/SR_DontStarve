#pragma once

#include "Include.h"
#include "GameObject.h"

BEGIN(Engine)
class CTexture;
class CCollider;
END

class CWall : public Engine::CGameObject
{
	friend class CRoom;
public:
	explicit CWall(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CWall();


	virtual void OnCollisionEnter(const class Collision* collision) override;
	virtual void OnCollisionStay(const class Collision* collision) override;
	virtual void OnCollisionExit(const class Collision* collision) override;

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	CCollider*	m_pCollider;

private:
	Engine::CTexture*	m_pTextureCom;

	virtual HRESULT Add_Component() override;

public:
	static CWall*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};