#pragma once
#include "Bullet.h"

BEGIN(Engine)
class CTexture;
class CRcTex;
class CAnimation;
END

class CVortexBullet : public CBullet
{
	friend class CBulletPool;
private:
	explicit CVortexBullet(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CVortexBullet();

public:
	virtual void SetDead(_bool bDead = true) override;

	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;


	virtual void OnCollisionEnter(const Collision* collsion) override;
	virtual void OnCollisionStay(const Collision* collision) override;
	virtual void OnCollisionExit(const Collision* collision) override;

	virtual HRESULT Add_Component() override;

public:
	virtual void Pop_Initialize();

protected:
	virtual void Free(void) override;

private:
	// 총알은 매니저를 통해서 생성할것.
	static CVortexBullet*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	_bool		m_bHit;

	CTexture*	m_BeforeTexture;
	CTexture*	m_AfterTexture;
	CRcTex*		m_RcTex;
	CAnimation*	m_Animation;
};

