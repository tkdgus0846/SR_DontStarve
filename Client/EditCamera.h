#pragma once
#include "GameObject.h"

BEGIN(Engine)
class CCamera;
class CTexture;
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

public:
	void Set_Tag(const _tchar* Tiletag) { m_Tiletag = Tiletag; }
	PICK_TYPE& Get_Pick() { return m_ePick; }
	ClickInfo&	Get_ClickInfo() { return m_tPickInfo; }
	void CreateMonster();
	void CreateTile();
	_int&	Get_Radio() { return m_radio; }

private:
	void LoadSaveTarget(const _tchar* tag);

private:
	void SetClickInfo();

	// Functions that fill in mouse click information
	_bool IntersectRayRoom(IN const CRoom* pRoom, OUT CGameObject*& pGameObject, OUT Triangle& tri, OUT INDEX32& index, OUT float& fDist);
	_bool IntersectRayGameObject(IN CGameObject* pGameObject, OUT Triangle& tri, OUT INDEX32& index, OUT float& fDist);
	_bool Compute_RayCastHitGameObject(IN Ray* pRay, IN CGameObject* pGameObject, OUT Triangle& tri, OUT INDEX32& index, OUT float& fDist);
	Ray CalcRaycast(POINT ptMouse);
	POINT GetMousePos();

	// 
	_vec3 CalcMiddlePoint(Triangle& tri);

private:
	_float				m_fSpeed;
	_bool				m_bFix;
	PICK_TYPE			m_ePick;
	CRoom*				tmp;
	ClickInfo			m_tPickInfo;
	const _tchar*		m_pCurTextureName;
	const _tchar*		m_Tiletag;

	_int				m_radio;
public:
	static CEditCamera*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;
};

