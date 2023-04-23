#pragma once
#include "Monster.h"

BEGIN(Engine)
class CAnimation;
END

class CWormHead;
class CWormTail;
class CWormBody : public CMonster
{
private:
	explicit CWormBody(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CWormBody();

public:
	virtual HRESULT Ready_GameObject(const _vec3& vPos);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	void Chain_Head(CWormHead* pHead) { m_pHead = pHead; }
	void Chain_Front(CWormBody* pBody) { m_pFrontBody = pBody; }
	void Chain_Back(CWormBody* pBody) { m_pBackBody = pBody; }
	void Chain_Tail(CWormTail* pTail) { m_pTail = pTail; }
	void Set_Dest(const _vec3& vPos) { m_vDest = vPos; }
	void Set_Move(_bool bSwitch) { m_bMove = bSwitch; }
	_bool Get_Move() { return m_bMove; }

private:
	virtual HRESULT Add_Component() override;
	void Move(const _float& fTimeDelta);

private:
	Engine::CAnimation*	m_pAnimation;

	CWormHead*	m_pHead;
	CWormBody*	m_pFrontBody;
	CWormBody*	m_pBackBody;
	CWormTail*	m_pTail;
	_vec3		m_vDest;
	_bool		m_bMove;
	_float		m_fCurAngle;
	_float		m_fPreAngle;
	_float		m_fCurTime;
	_float		m_fPreTime;

public:
	static CGameObject*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos);
	
private:
	virtual void Free(void) override;
};

