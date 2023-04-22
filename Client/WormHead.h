#pragma once
#include "Monster.h"

BEGIN(Engine)
class CAnimation;
END

class CWormBody;
class CWormTail;
class CWormHead : public CMonster
{
private:
	explicit CWormHead(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CWormHead();

public:
	virtual HRESULT Ready_GameObject(const _vec3& vPos);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	void Set_Move(_bool bSwitch) { m_bMove = bSwitch; }
	_bool Get_Move() { return m_bMove; }

private:
	virtual HRESULT Add_Component() override;

private:
	Engine::CAnimation*	m_pAnimation;

	vector<CWormBody*>	m_vecBody;
	CWormTail*			m_pTail;
	_bool				m_bMove;
	_float				m_fCurAngle;
	_float				m_fPreAngle;
	_float				m_fCurTime;
	_float				m_fPreTime;

public:
	static CWormHead*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos);

private:
	virtual void Free(void) override;
};

