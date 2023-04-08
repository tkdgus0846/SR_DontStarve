#pragma once
#include "GameObject.h"

BEGIN(Engine)
class CCamera;
END

class CRoom;
class CEditCamera : public CGameObject
{
private:
	explicit CEditCamera(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CEditCamera();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	virtual	HRESULT Add_Component() override;
	void	Key_Input(const _float& fTimeDelta);
	void	Mouse_Move(const _float& fTimeDelta);
	void	Fix_Mouse();

	_bool IntersectRayRoom(IN CRoom* pRoom, OUT Triangle& tri);

private:
	_bool IntersectRayGameObject(IN CGameObject* pGameObject, OUT Triangle& tri);
	_bool Compute_RayCastHitGameObject(IN Ray* pRay, IN CGameObject* pGameObject, OUT Triangle& tri);
	Ray CalcRaycast(POINT ptMouse);
	POINT GetMousePos();
	_vec3 CalcMiddlePoint(Triangle& tri);

private:
	_float				m_fSpeed;
	_bool				m_bFix;
	CRoom*				tmp;

public:
	static CEditCamera*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;
};

