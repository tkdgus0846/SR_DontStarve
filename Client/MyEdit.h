#pragma once

#include "Scene.h"

#ifdef _IMGUI
<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "imgui.h"
#include "ImManager.h"
#endif

#endif

class CMyEdit : public CScene
{
private:
	explicit CMyEdit(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CMyEdit();

public:
	virtual HRESULT		Ready_Scene(void) override;
	virtual _int		Update_Scene(const _float& fTimeDelta)override;
	virtual void		LateUpdate_Scene(void)override;
	virtual void		Render_Scene(void) override;

public:
	static CMyEdit*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free(void);
};

