#pragma once

#include "Include.h"
#include "Creature.h"

BEGIN(Engine)

class CRcTex;
class CTexture;
class CCollider;
class CRigidbody;
class CCamera;
END

class CPlayer : public CCreature
{
private:
	explicit CPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CPlayer();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;


	virtual void OnCollisionEnter(const Collision* collsion) override;
	virtual void OnCollisionStay(const Collision* collision) override;
	virtual void OnCollisionExit(const Collision* collision) override;

	void			Change_Weapon(WEAPONTYPE eWeaponType);
	void			Next_Weapon();
	void			Prev_Weapon();
	void			Gain_Weapon(WEAPONTYPE eWeaponType);
	class CWeapon*	Get_CurWeapon() const { return m_pCurWeapon; }
	WEAPONTYPE		Get_CurWeaponType() const { return m_eCurWeaponType; }

	void			Gain_Coin() {}
	void			Gain_Hp(_int Hp = 1) { m_iHp += Hp; }

private:
	virtual HRESULT Add_Component() override;
	void		Key_Input(const _float& fTimeDelta);
	void		Mouse_Move(const _float& fTimeDelta);
	void		Fix_Mouse();

private:
	_bool					m_bFix;

	array<class CWeapon*, WEAPONEND>	m_MyWeaponList;
	class CWeapon*						m_pCurWeapon;
	WEAPONTYPE							m_eCurWeaponType;

public:
	static CPlayer*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;

};

