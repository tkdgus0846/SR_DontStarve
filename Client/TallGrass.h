#pragma once
#include "MapObj.h"
class CTallGrass :
	public CMapObj
{
protected:
	explicit CTallGrass(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CTallGrass();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	virtual HRESULT Add_Component() override;

	static CGameObject*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"TallGrass"; }

protected:
	virtual void Free(void) override;
};

