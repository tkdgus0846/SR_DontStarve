#pragma once
#include "MapObj.h"
class CPyramid :
	public CMapObj
{
private:
	explicit CPyramid(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CPyramid();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	virtual void OnCollisionEnter(const Collision* collsion) override;
	virtual void OnCollisionStay(const Collision* collision) override;
	virtual void OnCollisionExit(const Collision* collision) override;

	virtual HRESULT Add_Component() override;
	static CPyramid*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void Free(void) override;
};

