#pragma once
#include "Component.h"

BEGIN(Engine)

struct AnimFrame
{
	_bool bRepeat;
	_float fFrameSpeed; // 초 단위로 넣으면 된다.
	_float fAccTime;
	_uint iMaxFrame;
	_uint iFrame;
	class CTexture* pTexture;
	
};

class CAnimation : public CComponent
{
private:
	explicit CAnimation(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CAnimation(const CAnimation& rhs);
	virtual ~CAnimation();

public:
	HRESULT Ready_Animation();
	virtual _int Update_Component(const _float& fTimeDelta) override;
	virtual void LateUpdate_Component() override;
	virtual void Render_Component() override;

	static CAnimation* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent* Clone(void) override;
	virtual void Free(void) override;

public:
	void SelectState(ANIMSTATE state);
	void BindAnimation(ANIMSTATE state, CTexture* texture, float frameSpeed = 0.5f, bool repeat = TRUE);
	_bool GetFinished() const { return m_bFinished; }
	void AnimationClear() { m_bFinished = false; m_CurFrame->iFrame = 0; }

private:
	unordered_map<ANIMSTATE, AnimFrame> m_MapAnimation;
	AnimFrame* m_CurFrame;

	ANIMSTATE m_ePrevState;
	ANIMSTATE m_eCurState;

	_bool	  m_bFinished;
};

END