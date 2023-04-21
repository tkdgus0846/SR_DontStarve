#pragma once
#include "GameObject.h"

BEGIN(Engine)
class CAnimation;
END

class CSonic : public CGameObject
{
private:
	explicit CSonic(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSonic();

	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	void		Key_Input(const _float& fTimeDelta);
	void		Jump(const _float& fTimeDelta);

private:
	virtual HRESULT Add_Component() override;

public:
	static CSonic*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	CAnimation*		m_pAnimation;
	_matrix			m_ViewMat;
	_matrix			m_Projmat;
	_float			m_fForce;
	_float			m_fTime;
};

