#pragma once
#include "Tile.h"

class CFloorTile :
	public CTile
{
protected:
	explicit CFloorTile(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CFloorTile();

	Vertex4 Get_PlaneXZ();
	_bool IntersectPoint(const _vec3* vPoint);
	void Set_Trigger(_bool bTrigger = true) { m_bTrigger = bTrigger; }
	const _bool& IsTrigger() { return m_bTrigger; }
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
public:
	virtual void InteractGameObject(const InteractInfo* tInteractInfo);

protected:
	_bool	m_bTrigger = false;
};