#pragma once

#include "Base.h"
#include "Layer.h"

BEGIN(Engine)

class  CScene : public CBase
{
	friend class CManagement;
protected:
	explicit CScene(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CScene();

public:
	CComponent*			Get_Component(LAYERID LayerID, const _tchar* pObjTag, const _tchar* pComponentTag, COMPONENTID eID);

public:
	virtual HRESULT		Ready_Scene(void)PURE;
	virtual _int		Update_Scene(const _float& fTimeDelta);
	virtual void		LateUpdate_Scene(void);
	virtual void		Render_Scene(void)PURE;

protected:
	HRESULT Add_GameObject(LAYERID LayerID, const _tchar* pObjTag, class CGameObject* pObj);

protected:
	LPDIRECT3DDEVICE9			m_pGraphicDev;
	array<CLayer*, LAYER_END>	m_arrLayer;

protected:
	virtual void	Free(void);
};

END