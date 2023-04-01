#pragma once

#include "Include.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "imgui.h"

// 엔진 컴포넌트 사용예시
BEGIN(Engine)

class CGameObject;

END

class CImWindow
{
protected:
	explicit CImWindow();
public:
	virtual ~CImWindow();

public:
	virtual HRESULT Ready_ImWindow(CGameObject* pGameObject);
	virtual _int Update(float fTimeDelta) PURE;

	// 생성함수는 항상 정의하기.
// public:
	// static CImWindow Create(CGameObject* pGameObject);
private:
	virtual void Free(void) PURE;

protected:
	CGameObject* m_pTarget;


};