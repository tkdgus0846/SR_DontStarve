#pragma once

#include "Base.h"

BEGIN(Engine)

class CScene;
class CComponent;

class  CManagement : public CBase
{
	DECLARE_SINGLETON(CManagement)

private:
	explicit CManagement();
	virtual ~CManagement();

public:
	CComponent*			Get_Component(LAYERID LayerID, const _tchar* pObjTag, const _tchar* pComponentTag, COMPONENTID eID);

public:
	HRESULT			Set_Scene(CScene* pScene);

	_int			Update_Management(const _float& fTimeDelta);
	void			LateUpdate_Management();
	void			Render_Management(LPDIRECT3DDEVICE9 pGraphicDev);

	void			Add_GameObject(class CGameObject* pObj);
	CGameObject*	Get_GameObject(LAYERID LayerID, const _tchar* pObjTag);

	// 플레이어를 전역적으로 불러옴.
	class CGameObject*	Get_Player();
	void				Set_Player(CGameObject* player);

	void				Start_WorldTimer();
	void				Stop_WorldTimer();
	_float				Get_WorldTime() const { return m_fWorldTime; }

private:
	CScene*			m_pScene = nullptr;
	class CGameObject*	m_pPlayer;

	_float			m_fWorldTime;
	_bool			m_bPlayingWorldTimer;

private:
	virtual void	Free(void);
};

END