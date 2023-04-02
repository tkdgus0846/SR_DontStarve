#pragma once
#include "Component.h"

BEGIN(Engine)

class CBlackBoard;
class CBehavior : public CComposite
{
protected:
	explicit CBehavior(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CBehavior(const CBehavior& rhs);
	virtual ~CBehavior();

public:
	virtual HRESULT Ready_Behavior();
	virtual _int	Update_Component(const _float& fTimeDelta);
	virtual void	LateUpdate_Component(void);
	virtual void	Render_Component(void);

public:
	void Set_BlackBoard(CBlackBoard* pBlackBoard) { m_pBlackBoard = pBlackBoard; }

public:
	CBlackBoard* m_pBlackBoard;

protected:
	virtual CComponent * Clone(void) PURE;

protected:
	virtual void Free() override;
};

END