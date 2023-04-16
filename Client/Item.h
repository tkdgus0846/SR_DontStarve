#pragma once
#include "GameObject.h"

BEGIN(Engine)

class CAnimation;
class CTexture;

END

class CPlayer;
class CItem : public CGameObject
{
protected:
	explicit CItem(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CItem();

public:
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void OnCollisionEnter(const class Collision* collsion) override;
	virtual void OnCollisionStay(const class Collision* collision) override;

	void		Set_Loot(_bool state = true) { m_bCanLoot = state; }
	_bool		Get_Loot() const { return m_bCanLoot; }

public:
	class CAnimation* m_pAniCom;
	class CTexture*   m_pTextureCom;
	
protected:
	_bool					m_bDrop;
	_bool					m_bBill;
	_float					m_fY;
	_float					m_fSpeed;
	_float					m_fMaxY;
	_float					m_fMinY;
	_bool					m_bCanLoot;

protected:
	virtual void		ItemPatrol(const _float& fTimeDelta);
	virtual void		ItemMagnetic(CPlayer* pPlayer);
	virtual void		ItemDrop(const _float & fTimeDelta);

private:
	_float m_fTime;

protected:
	virtual void Free() override;
};