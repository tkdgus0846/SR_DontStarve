#pragma once

#include "Base.h"
#include "Scene.h"

BEGIN(Engine)

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

	void			Add_GameObject(LAYERID LayerID, const _tchar* pObjTag, class CGameObject* pObj);

	// �÷��̾ ���������� �ҷ���.
	class CGameObject*	Get_Player();
	void				Set_Player(CGameObject* player);

private:
	CScene*			m_pScene = nullptr;
	class CGameObject*	m_pPlayer;

private:
	virtual void	Free(void);
};

END