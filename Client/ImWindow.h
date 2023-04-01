#pragma once

#include "Include.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "imgui.h"

// ���� ������Ʈ ��뿹��
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

	// �����Լ��� �׻� �����ϱ�.
// public:
	// static CImWindow Create(CGameObject* pGameObject);
private:
	virtual void Free(void) PURE;

protected:
	CGameObject* m_pTarget;


};