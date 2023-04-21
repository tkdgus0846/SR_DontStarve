#pragma once

#include "Base.h"
#include "Include.h"

BEGIN(Engine)

class CLayer;
class CComponent;

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

	void				Set_StaticLayerArr(vector<CLayer*>* layerArr);
	void				Remove_GameObject(LAYERID layerID, class CGameObject* obj);

	void				Reset_Scene();
	HRESULT			Add_GameObject(class CGameObject* pObj);

protected:
	
	CGameObject*	Get_GameObject(LAYERID LayerID, const _tchar* pObjTag);
	void			Play_SlowTime(const _float & fTimeDelta);
	void			Reset_SlowTime(const _float & fTimeDelta);

public:
	CLayer* Get_Layer(LAYERID LayerID);

protected:
	LPDIRECT3DDEVICE9			m_pGraphicDev;

	vector<CLayer*>*	m_StaticLayerArr;
	vector<CLayer*>		m_DynamicLayerArr;

	_float				m_SlowTime;
  
protected:
	virtual void	Free(void);
};

END