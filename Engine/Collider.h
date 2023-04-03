#pragma once
#include "Component.h"

BEGIN(Engine)

class CCollider : public CComponent
{
protected:
	explicit CCollider(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CCollider(const CCollider& rhs);
	virtual ~CCollider();

protected:
	// ���� ����
	BoundingBox* m_pBoundingBox;
	// �簢�� ������
	LPD3DXMESH			m_pMesh;
	COLGROUP			m_eGroup;
	// ���� �浹���� ��� �ݶ��̴����� ���� -> ��������� ������ �ʿ� ����. �ǽð� ����
	map<CCollider*, Collision*>	m_Colmap;
public:
	HRESULT	Ready_Collider();
	virtual _int Update_Component(const _float& fTimeDelta) override;
	virtual void LateUpdate_Component() override;
	virtual void Render_Component() override;
public:
	void Set_Group(COLGROUP eGroup);
	COLGROUP Get_Group() { return m_eGroup; }
	void Get_Point(_vec3* MinPoint, _vec3* MaxPoint)
	{
		*MinPoint = m_pBoundingBox->_min;
		*MaxPoint = m_pBoundingBox->_max;
	}
	// ���� �浹�� �Ͼ ��� �ݶ��̴�, ���°� ����
	void Insert_Collider(CCollider* pCollider, COL_DIR eDir);
	// �ʾȿ� �ش��ϴ� �ݶ��̴��� ���°��� ��ȯ
	Collision* Find_ColState(class CCollider* pOtherCol);
	// �̹� ����Ʈ�� �ִ��� üũ�ϴ� �Լ�
	_bool	Check_AlreadyCol(class CCollider* pOtherCol);
	_bool Delete_OtherCollider(CCollider* pOtherCol);

	bool Intersect(const _vec3& point) { return m_pBoundingBox->Intersect(point); }
	_vec3 Get_BoundCenter() { return m_pBoundingBox->Get_Center(); }
	_vec3 Get_BoundSize() { return m_pBoundingBox->Get_Size();}
	void OnCollisionEnter(const Collision* collision);
	void OnCollisionStay(const Collision* collision);
	void OnCollisionExit(const Collision* collision);

	void Set_BoundingBox(const _vec3& vSize = {2.f, 2.f, 2.f});

public:
	static CCollider* Create(LPDIRECT3DDEVICE9 pGraphicDev, _bool bIsTrigger);
	virtual CComponent * Clone(void) override;
private:
	virtual void Free(void) override;
};

END