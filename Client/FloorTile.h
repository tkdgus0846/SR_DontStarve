#pragma once
#include "Tile.h"
#include "ImInspector.h"

BEGIN(Engine)

class CRcTex;
class CTexture;

END

class CFloorTile :
	public CTile
{
	friend class CInspector;
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
	static CFloorTile* Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 vPos);

private:
	virtual void Free(void) override;	
};