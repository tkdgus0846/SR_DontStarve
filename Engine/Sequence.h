#pragma once
#include "Behavior.h"

/*
	시퀀스
	시퀀스는 왼쪽부터 오른쪽으로 차례대로 behavior를 순회하면서
	하나라도 리턴값이 FALSE일 경우 순회를 멈추고 FALSE를 반환한다.
	그리고 모든 behavior를 순회 했으면 TRUE를 반환한다.
*/

BEGIN(Engine)

class CBlackBoard;
class CSequence : public CBehavior
{
private:
	explicit CSequence(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSequence(const CSequence& rhs);
	virtual ~CSequence();
	
public:
	virtual HRESULT Ready_Behavior() override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override;
	virtual void Render_Component(void) override;

public:
	static CSequence* Create(LPDIRECT3DDEVICE9 pGraphiDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

END