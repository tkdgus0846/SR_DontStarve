#pragma once

#include "Include.h"
#include "GameObject.h"

BEGIN(Engine)

class CRcTex;
class CTexture;
class CCollider;
class CRigidbody;
class CCamera;
END
class CPlayer : public Engine::CGameObject
{
private:
	explicit CPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CPlayer();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;


	virtual void OnTriggerStay(const class CCollider* other);
private:
	virtual HRESULT Add_Component() override;
	void		Key_Input(const _float& fTimeDelta);
	void		Mouse_Move(const _float& fTimeDelta);
	void		Fix_Mouse();

private:
	Engine::CRcTex*			m_pBufferCom;
	Engine::CTexture*		m_pTextureCom;
	Engine::CCollider*		m_pCollider;
	Engine::CRigidbody*		m_pRigid;
	Engine::CCamera*		m_pCamera;

	_float					m_fSpeed;

	_bool					m_bFix;

public:
	static CPlayer*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;

};

