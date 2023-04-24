#pragma once

#include "Include.h"
#include "Creature.h"

BEGIN(Engine)

class CRcTex;
class CTexture;
class CCollider;
class CRigidbody;
class CCamera;
class CLayer;
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

	void			Gain_Coin(_int coin = 1) { m_iCoin += coin; }
	_int			Get_Coin() { return m_iCoin; }
	_bool			De_Coin(_int coin) 
	{ 
		if (m_iCoin - coin < 0) return false;
		m_iCoin -= coin; 
		return true;
	}
	_vec3			GetDeltaVec();
	void			Gain_Disc(_int disc = 1) { m_iDisc += disc; }
	_int			Get_Disc() { return m_iDisc; }
	void			Gain_Hp(_int Hp = 1) { m_iHp += Hp; }
	void			Gain_UltiGuage(_int guage = 1) { m_fUltimateGuage += guage; }
	_int			Get_UltiGuage() { return m_fUltimateGuage; }
	_int			Get_UltiMaxGuage() { return m_fUltimateMax; }

	void			AimHack();
	void			Fix_Aim(CCollider* pCollider);
	_vec3			Tactical_Bullet_Dir();
	
	bool IsObjectInFOV(_float fDistance, _float fRadius, _float fFov);
	void			IsOnIceTile(_bool _IsOnIceTile) {
		m_bIsOnIceTile = _IsOnIceTile;	}


	virtual void Get_Damaged(_int Damage) override;

private:
	virtual HRESULT Add_Component() override;
	void		Key_Input(const _float& fTimeDelta);
	void		Mouse_Move(const _float& fTimeDelta);
	void		Fix_Mouse();
	void		InteractTile(_float fTimeDelta);
private:
	_bool					m_bFix;

	_bool					m_bAimHack = false;
	_float					m_AimHackTime = 0.f;
	_bool					m_bTactic = false;
	_float					m_TacticTime = 0.f;

	_int					m_iCoin;
	_int					m_iDisc = 0;

	_float					m_fUltimateMax = 100.f;
	_float					m_fUltimateGuage = 0.f;

	_bool					m_bInvicible;

	array<class CWeapon*, WEAPONEND>	m_MyWeaponList;
	class CWeapon*						m_pCurWeapon;
	WEAPONTYPE							m_eCurWeaponType;

	vector<CGameObject*>				m_vecMonster;
	list<_vec3>							m_PosList;

	_bool				m_bIsOnIceTile = false;
public:
	static CPlayer*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;

};

