#pragma once

#include "Base.h"
#include "Include.h"

BEGIN(Engine)

class CComponent : public CBase
{
	friend class CProtoMgr;
	friend class CComposite;

protected:
	explicit CComponent();
	explicit CComponent(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CComponent(const CComponent& rhs);
	virtual ~CComponent();

public:
	virtual			_int	Update_Component(const _float& fTimeDelta) { return 0; }
	virtual			void	LateUpdate_Component() {}
	virtual			void	Render_Component() {}

	CComponent*			Get_Component(const _tchar* pComponentTag, COMPONENTID eID);
	class CGameObject*	Get_GameObject() const { return m_pGameObject; }

protected:
	LPDIRECT3DDEVICE9	m_pGraphicDev;
	_bool				m_bClone;
	class CGameObject*	m_pGameObject;

public:
	virtual	CComponent*	Clone(void) PURE;
	virtual void		Free(void)override;

private:
	void SetOwner(class CGameObject* gameObject);
};

typedef struct tagComponent
{
	_int			iPriority;
	const _tchar*	pTag;
	CComponent*		pComponent;
}COMPONENT;

class CComposite : public CComponent
{
protected:
	explicit CComposite();
	explicit CComposite(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CComposite(const CComposite& rhs);
	virtual ~CComposite();

public:
	virtual HRESULT		Ready_Composite(void);
	virtual _int		Update_Component(const _float& fTimeDelta);
	virtual void		LateUpdate_Component(void);
	virtual void		Render_Component(void);

public:
	HRESULT				Add_Component(COMPONENTID eID, 
										const _int& iPriority, 
										const _tchar* pComponentTag, 
										CComponent* pComponent);
	virtual void		Free(void) override;

protected:
	vector<COMPONENT>			m_VecComponents[ID_END];
	vector<COMPONENT>::iterator m_iterCurComponent;
	vector<COMPONENT>::iterator m_iterPreComponent;
};

END