#pragma once

#include "Component.h"
#include "Base.h"

BEGIN(Engine)

class  CGameObject : public CBase
{
protected:
	explicit CGameObject(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CGameObject();

public:
	CComponent*			Get_Component(const _tchar* pComponentTag, COMPONENTID eID);
	_float				Get_ViewZ(void) { return m_fViewZ; }


	// 순수 가상함수 왜냐하면 게임오브젝트에 컴포넌트가 추가되지 않을일은 없으니까
	virtual HRESULT		Add_Component() PURE;

public:
	virtual HRESULT		Ready_GameObject(void);
	virtual _int		Update_GameObject(const _float& fTimeDelta);
	virtual void		LateUpdate_GameObject(void);
	virtual void		Render_GameObject(void);

	virtual void OnCollisionEnter(const class Collision* collsion) {}
	virtual void OnCollisionStay(const class Collision* collision) {}
	virtual void OnCollisionExit(const class Collision* collision) {}

	virtual void OnTriggerEnter(const class CCollider* other) {}
	virtual void OnTriggerStay(const class CCollider* other) {}
	virtual void OnTirggerExit(const class CCollider* other) {}

	void			Compute_ViewZ(const _vec3* pPos);

	// 위치 지정 함수
	void			Set_Pos(const _vec3& pos);
	// 쳐다보는 방향 바꾸는 함수
	void			Set_Dir(const _vec3& dir);

private:
	CComponent*			Find_Component(const _tchar* pComponentTag, COMPONENTID eID);
	

protected:
	unordered_map<const _tchar*, CComponent*>			m_uMapComponent[ID_END];
	LPDIRECT3DDEVICE9		m_pGraphicDev;
	_float					m_fViewZ = 0.f;

public:
	class CTransform* m_pTransform;

protected:
	virtual void		Free(void);
};

END