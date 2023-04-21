#pragma once
#include "GameObject.h"

class CLoadingBackground : public CGameObject
{
private:
	explicit CLoadingBackground(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CLoadingBackground();

public:
	static CLoadingBackground*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual HRESULT Add_Component() override;


	virtual void Render_GameObject(void) override;

private:
	_matrix m_IdentityMatrix;


	


};

