#pragma once
#include "Bullet.h"

class CNormalBullet : public CBullet
{
	friend class CBulletPool;
private:
	explicit CNormalBullet(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CNormalBullet();

public:
	virtual void SetDead() override;

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
	static CNormalBullet*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

};

