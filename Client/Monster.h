#pragma once

#include "Include.h"
#include "GameObject.h"

BEGIN(Engine)

class CTriCol;
class CTransform;
class CCollider;

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
	HRESULT		Add_Component(void);

protected:
	HRESULT		Set_Patrol_AI();

private:
	Engine::CTriCol*	m_pBufferCom;
	Engine::CCollider*	m_pCollider;
	Engine::CCollider*	m_pRange;

	_float				m_fSpeed;

public:
	static CMonster*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;

};

