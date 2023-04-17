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
//
//struct ZComp
//{
//	const bool operator()(CGameObject* a, CGameObject* b)
//	{
//		return a->m_pTransform->m_vInfo[INFO_POS].z < b->m_pTransform->m_vInfo[INFO_POS].z;
//	}
//};

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
	void			Gain_Disc(_int disc = 1) { m_iDisc += disc; }
	_int			Get_Disc() { return m_iDisc; }
	void			Gain_Hp(_int Hp = 1) { m_iHp += Hp; }
	void			Gain_UltiGuage(_int guage = 1) { m_fUltimateGuage += guage; }
	_int			Get_UltiGuage() { return m_fUltimateGuage; }
	_int			Get_UltiMaxGuage() { return m_fUltimateMax; }

	void			AimHack();


private:
	virtual HRESULT Add_Component() override;
	void		Key_Input(const _float& fTimeDelta);
	void		Mouse_Move(const _float& fTimeDelta);
	void		Fix_Mouse();

private:
	_bool					m_bFix;

	_int					m_iCoin = 777;
	_int					m_iDisc = 0;

	_float					m_fUltimateMax = 100.f;
	_float					m_fUltimateGuage = 0.f;

	array<class CWeapon*, WEAPONEND>	m_MyWeaponList;
	class CWeapon*						m_pCurWeapon;
	WEAPONTYPE							m_eCurWeaponType;

	vector<CGameObject*>				m_vecMonster;

public:
	static CPlayer*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;

};

