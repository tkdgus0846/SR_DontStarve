#pragma once
#include "Component.h"

/*
	BehaviorƮ���� ������Ҵ� ������ ����.
	Root	-	ai Ʈ���� ���۴ܰ�. ������(BlackBoard.h ����.)�� ������ ������
				��� ai�� ������ root�� ������ �ִ�.

	Selector-	ai�� ���� �и��� ����1. �������� OR ����� ����� ���۹����
				������ ������, �ϳ��� ����̶� True�� ��ȯ�� ��� False�� ��ȯ�Ѵ�.
				�׸��� ��� ����� ��ȸ �� ��� True�� ��ȯ�Ѵ�.

	Sequence-	ai�� ���� �и��� ����2. �������� AND ����� ����� ���۹����
				������ ������, �ϳ��� ����̶� False�� ��ȯ�� ��� False�� ��ȯ�Ѵ�.
				�׸��� ��� ����� ��ȸ �� ��� True�� ��ȯ�Ѵ�.

	Task	-	ai�� ���� ��ɺ�. ai�� ����� ����ϰ� ������, ���α׷��Ӱ�
				�ʿ��� ��� BehaviorŬ������ ��ӹ޾Ƽ� ����� �����ϸ� �ȴ�.
	
	�� �� ���α׷��Ӱ� ���������� ������ �ô� �κ��� Task �κ��̴�.

	�дٰ� �𸣴� ������ ���� ��� �ּ�ȯ ���� �������
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