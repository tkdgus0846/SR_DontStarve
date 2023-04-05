#pragma once
#include "Component.h"

/*
	BehaviorƮ���� ������Ҵ� ������ ����.
	Root	-	ai Ʈ���� ���۴ܰ�. �����带 ������ ������ ��� ai�� 
				������ root�� ������ �ִ�.

	Selector-	ai�� ���� �и��� ����1. �������� OR ����� ����� ���۹����
				������ ������, �ϳ��� ����̶� True�� ��ȯ�� ��� False�� ��ȯ�Ѵ�.
				�׸��� ��� ����� ��ȸ �� ��� True�� ��ȯ�Ѵ�.

	Sequence-	ai�� ���� �и��� ����2. �������� AND ����� ����� ���۹����
				������ ������, �ϳ��� ����̶� False�� ��ȯ�� ��� False�� ��ȯ�Ѵ�.
				�׸��� ��� ����� ��ȸ �� ��� True�� ��ȯ�Ѵ�.

	Task	-	ai�� ���� ��ɺ�. ai�� ����� ����ϰ� ������, ���α׷��Ӱ�
				�ʿ��� ��� BehaviorŬ������ ��ӹ޾Ƽ� ����� �����ϸ� �ȴ�.
	
	�� �� ���α׷��Ӱ� ���������� ������ �ô� �κ��� Task �κ��̴�.
*/

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

	HRESULT			Add_Decorator(CComponent* pComponent);

protected:
	_int			update_Decorator(const _float& fTimeDelta);

protected:
	list<PRICOMP> m_DecoratorList;

public:
	CBlackBoard* m_pBlackBoard;

protected:
	virtual CComponent * Clone(void) PURE;

protected:
	virtual void Free() override;
};

END