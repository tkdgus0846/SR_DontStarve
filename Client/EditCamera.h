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
	_bool& Get_Pick(PICK_TYPE ePickType) { return m_bPick[ePickType]; }
	ClickInfo&	Get_ClickInfo() { return m_tPickInfo; }

private:
	// imgui에서 사용하는 함수들로 bool변수로 활성화 여부를 결정.
	// ex) m_bPick[PICK_TILE]를 true로 만들어주면 CreateTile이 활성화된다.
	void CreateTile();
	void CreateObj(const _tchar* tag, _vec3 vPos = {0.f, 0.f, 0.f});

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
public:
	void Change_Texture(const _tchar* pTextureName) { m_pCurTextureName = pTextureName; }

private:
	_float				m_fSpeed;
	_bool				m_bFix;
	_bool				m_bPick[PICK_END];
	CRoom*				tmp;
	ClickInfo			m_tPickInfo;
	const _tchar*		m_pCurTextureName;

public:
	static CEditCamera*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;
};

