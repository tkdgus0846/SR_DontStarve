#pragma once
#include "Base.h"
#include "Include.h"

BEGIN(Engine)

class  CTimer : public CBase
{
private:
	explicit CTimer();
	virtual ~CTimer();

public:
	_float		Get_TimeDelta(void) { return m_fTimeDelta; }

public:
	HRESULT		Ready_Timer(void);
	void		Update_Timer(void);
	
private:
	LARGE_INTEGER			m_tFrameTime;
	LARGE_INTEGER			m_tFixTime;
	LARGE_INTEGER			m_tLastTime;
	LARGE_INTEGER			m_CpuTick;

	_float					m_fTimeDelta;

public:
	static CTimer*		Create(void);
	virtual void		Free(void)override;
};

END
