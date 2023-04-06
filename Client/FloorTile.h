#pragma once
#include "Tile.h"


BEGIN(Engine)

class CRcTex;
class CTexture;

END

class CFloorTile :
	public CTile
{
private:
	explicit CFloorTile(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CFloorTile();

private:
	virtual HRESULT Ready_GameObject(void) override;
public:
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

public:
	virtual HRESULT Add_Component() override;
	static CFloorTile* Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 vPos);

private:
	Engine::CRcTex*		m_pBufferCom;
	Engine::CTexture*	m_pTextureCom;

private:
	virtual void Free(void) override;	
};