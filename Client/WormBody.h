#pragma once
#include "Monster.h"

BEGIN(Engine)
class CAnimation;
END

class CWormHead;
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
	void Set_Dest(const _vec3& vPos) { m_vDest = vPos; }
	void Set_Move(_bool bSwitch) { m_bMove = bSwitch; }

private:
	virtual HRESULT Add_Component() override;
	void Move(const _float& fTimeDelta);

private:
	Engine::CAnimation*	m_pAnimation;

	CWormHead*	m_pHead;
	CWormBody*	m_pFrontBody;
	CWormBody*	m_pBackBody;
	_vec3		m_vDest;
	_bool		m_bMove;

public:
	static CWormBody*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos);
	static const _tchar* GetTag() { return L"WormBody"; }

private:
	virtual void Free(void) override;
};

