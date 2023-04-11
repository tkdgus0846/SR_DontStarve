#pragma once

#include "Include.h"
#include "Creature.h"

BEGIN(Engine)

class CRoot;
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
	HRESULT		Create_Root_AI();			// AI 생성 시 제일 먼저 실행 시켜야 함.
	HRESULT		Set_PatrolAndFollow_AI();	// 줄여서 PAF
	HRESULT		Set_TurretAI();
	HRESULT		Set_PAF_JumpAI();
	HRESULT		Init_AI_Behaviours();		// AI작업 마지막에 무조건 실행 시켜야 함.

private:
	CRoot*		m_pRoot;	// 모든 몬스터는 하나의 ai를 가지는걸로 가정.

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