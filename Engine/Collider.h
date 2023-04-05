#pragma once
#include "Component.h"

BEGIN(Engine)

class CCollider : public CComponent
{
	friend class CCollisionMgr;

protected:
	explicit CCollider(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CCollider(const CCollider& rhs);
	virtual ~CCollider();

private:
	// 감지 영역
	BoundingBox*		m_pBoundingBox;
	// 사각형 렌더링
	LPD3DXMESH			m_pMesh;
	// 현재 충돌 중인 콜리젼들을 체크한다.
	unordered_map<CCollider*, Collision>	m_CollisionList;

	_bool				m_bEnabled;
	_bool				m_bIsRender;

	// 아래 두개 텍스쳐는 디버깅 용도로 넣었음. 나중에 지울거임.
	IDirect3DBaseTexture9*			m_GreenTexture;
	IDirect3DBaseTexture9*			m_RedTexture;

	
public:
	HRESULT			Ready_Collider();
	virtual _int	Update_Component(const _float& fTimeDelta) override;
	virtual void	LateUpdate_Component() override;
	virtual void	Render_Component() override;

public:
	void Get_Point(_vec3* MinPoint, _vec3* MaxPoint)
	{
		*MinPoint = m_pBoundingBox->_min;
		*MaxPoint = m_pBoundingBox->_max;
	}
	bool Intersect(const _vec3& point) { return m_pBoundingBox->Intersect(point); }
	_vec3 Get_BoundCenter() { return m_pBoundingBox->Get_Center(); }
	_vec3 Get_BoundSize() { return m_pBoundingBox->Get_Size();}

	void OnCollisionEnter(const Collision* collision);
	void OnCollisionStay(const Collision* collision);
	void OnCollisionExit(const Collision* collision);

	void Set_Enable(_bool bEnabled) { m_bEnabled = bEnabled; }
	_bool Get_Enable() const { return m_bEnabled; }
	void Toggle_IsRender() 
	{
		m_bIsRender = (m_bIsRender == true) ? false : true;
	}

	void Set_BoundingBox(const _vec3& vSize = {2.f, 2.f, 2.f});

public:
	static CCollider* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free(void) override;
};

END