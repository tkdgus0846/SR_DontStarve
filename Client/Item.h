#pragma once
#include "GameObject.h"

BEGIN(Engine)

class CAnimation;
class CTexture;

END

class CPlayer;
class CItem :
	public CGameObject
{
protected:
	explicit CItem(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CItem();

public:
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void OnCollisionEnter(const class Collision* collsion) override;

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

protected:
	virtual void		ItemPatrol();
	virtual void		ItemMagnetic(CPlayer* pPlayer);

protected:
	virtual void Free() override;
};