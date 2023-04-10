#pragma once

#include "GameObject.h"

BEGIN(Engine)
class CTexture;
class CCollider;
END

class CDoor : public CGameObject
{
private:
	explicit CDoor(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CDoor();

public:
	virtual HRESULT Ready_GameObject(const _vec3& vPos, _bool IsRot);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	virtual HRESULT Add_Component() override;

private:
	Engine::CTexture*		m_pTextureCom;
	Engine::CCollider*		m_pCollider;

public:
	static CDoor*		Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos, _bool IsRot = false);

private:
	virtual void Free(void) override;
};

