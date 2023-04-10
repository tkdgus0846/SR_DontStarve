#pragma once

#include "Include.h"
#include "Creature.h"

BEGIN(Engine)

class CTriCol;
class CTransform;
class CCollider;

END

class CMonster : public CCreature
{
protected:
	explicit CMonster(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CMonster();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	virtual void OnCollisionEnter(const class Collision* collsion);
	virtual void OnCollisionStay(const class Collision* collision);
	virtual void OnCollisionExit(const class Collision* collision);

private:
	virtual HRESULT Add_Component() override;

protected:
	HRESULT		Set_PatrolAndFollow_AI();
	HRESULT		Set_TurretAI();

protected:
	_float		m_fSpeed;

public:
	static CMonster*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void Free(void) override;
};

class MonsterFactory {
public:
	CGameObject* CreateMonster(const _tchar* tag);
};