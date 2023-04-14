#pragma once

#include "Include.h"
#include "Creature.h"

BEGIN(Engine)
class CRoot;
class CTriCol;
class CTransform;
class CCollider;
class CSequence;
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
	HRESULT		Init_AI_Behaviours();		// AI작업 마지막에 무조건 실행 시켜야 함.

	CSequence*	Make_Patrol_AI(const _float& fWaitTime = 1.f, const _float& fMoveTime = 0.5f);
	CSequence*	Make_Follow_AI(const _float& fTimer = 100.f);	// 디폴트값은 계속(이라고 하지만 아님) 쫒아옴
	CSequence*	Make_JumpAI(const _float& fTimer = 0.f);
	CSequence*	Make_DBJumpAI(const _float& fTimer = 1.f);
	CSequence*	Make_DBBackJumpAI(const _float& fTimer = 1.f);
	CSequence*	Make_LeapJumpAI(const _float& fTimer = 0.f);
	CSequence*	Make_JumpToPlayer();
	CSequence*	Make_RushAI();
	CSequence*	Make_BossPattern1(const _float& fCoolTime = 6.f);
	CSequence*	Make_BossPattern2(const _float& fCoolTime = 18.f);
	
	HRESULT		Set_PatrolAndFollow_AI();
	HRESULT		Set_PAF_JumpAI();
	HRESULT		Set_PAF_DBJumpAI();
	HRESULT		Set_PAF_LeapJumpAI();
	HRESULT		Set_TurretAI();
	HRESULT		Set_Boss1_AI();
	HRESULT		Set_Boss2_AI();

private:
	CRoot*		m_pRoot;	// 모든 몬스터는 하나의 ai를 가지는걸로 가정.

protected:
	// 빨갛게 반짝이는 효과를 결정하는 변수들
	// m_fDuration로 효과의 지속시간을 결정함.
	bool m_redTexture;
	float m_fDuration = 0.05f;
	float m_fCurTime;
	float m_fPreTime;

public:
	static CMonster*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void Free(void) override;
};