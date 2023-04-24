#pragma once
#include "Monster.h"

BEGIN(Engine)
class CAnimation;
END

class CTreeBoss : public CMonster
{
private:
	explicit CTreeBoss(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CTreeBoss();

public:
	virtual HRESULT Ready_GameObject(const _vec3& vPos);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	void Change_State() { m_bIsSummon == true ? false : true; }

private:
	_vec3 m_vDefaultPos;
	_bool m_bIsSummon;
	CAnimation* m_pAnimation;

private:
	virtual HRESULT Add_Component() override;

public:
	static CTreeBoss*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos);

private:
	virtual void Free(void) override;
};

