#pragma once
#include "Bullet.h"

class CShockWave : public CBullet
{
	friend class CBulletMgr;
	friend class CBulletPool;
private:
	explicit CShockWave(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CShockWave();

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

protected:
	virtual void Free(void) override;

private:
	// �Ѿ��� �Ŵ����� ���ؼ� �����Ұ�.
	static CShockWave*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
};

