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

protected:
	HRESULT			Add_GameObject(LAYERID LayerID, const _tchar* pObjTag, class CGameObject* pObj);
	CGameObject*	Get_GameObject(LAYERID LayerID, const _tchar* pObjTag);

private:
	CLayer* Get_Layer(LAYERID LayerID);

protected:
	LPDIRECT3DDEVICE9			m_pGraphicDev;

	vector<CLayer*>*	m_StaticLayerArr;
	vector<CLayer*>		m_DynamicLayerArr;
  
protected:
	virtual void	Free(void);
};

END