#pragma once

#include "Base.h"
#include "Include.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "imgui.h"


class CImWindow : public CBase
{
protected:
	explicit CImWindow(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CImWindow();

public:
	virtual HRESULT Ready_ImWindow();
	virtual _int Update(float fTimeDelta) PURE;

protected:
	void Toggle(bool& _bVariable);
	// 이거 헤더파일 2개 알려주면 사용가능

private:
	LPDIRECT3DDEVICE9 m_pGraphicDev;

protected:
	virtual void Free(void);
};