#pragma once

#include "Include.h"
#include "GameObject.h"

BEGIN(Engine)

class CTriCol;
class CTransform;
class CCollider;
class CRoot;

END

class CMonster : public Engine::CGameObject
{
private:
	explicit CMonster(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CMonster();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	virtual HRESULT Add_Component() override;

private:
	Engine::CTriCol*	m_pBufferCom;
	Engine::CCollider*	m_pCollider;
	Engine::CRoot*		m_pRoot;

	_float				m_fSpeed;

public:
	static CMonster*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;

};

