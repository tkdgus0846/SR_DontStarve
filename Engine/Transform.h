#pragma once

#include "Component.h"
#include "Include.h"

BEGIN(Engine)

class  CTransform : public CComponent
{
public:
	// ��������	  ��������
	enum MOVETYPE { LANDOBJECT, AIRCRAFT, MOVE_END };

private:
	explicit CTransform(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTransform(const CTransform& rhs);
	virtual ~CTransform();

public:
	const _matrix*		Get_WorldMatrixPointer() { return &m_matWorld; }
	void				Get_Info(INFO eType, _vec3* pInfo)
	{
		*pInfo = m_vInfo[eType];
	}
	const _vec3& Get_Scale()
	{
		return m_vScale;
	}

	void Set_Pos(const _float& x, const _float& y, const _float& z)
	{	
		m_vInfo[INFO_POS] = { x,y,z };
	}
	void Set_Pos(const _vec3& pos)
	{
		m_vInfo[INFO_POS] = pos;
	}

	// ����� ���ư����� Ȯ�� �غ�����.
	void Set_Dir(const _vec3& dir);

	// �ش� ��ġ�� �ٶ󺸰Բ� ����� �Լ�.
	void Set_Target(const _vec3& targetPos);

	// ������ ���ͷ� �����̴°�
	void	Move_Strafe(const _float& fUnits, const _float& fTimeDelta);// Move-Right

	// �� ���ͷ� �����̴°�
	void	Move_Fly(const _float& fUnits, const _float& fTimeDelta);	// Move-Up

	// �� ���ͷ� �����̴°�
	void	Move_Walk(const _float& fUnits, const _float& fTimeDelta);  // Move-Look

	void	Rot_Pitch(const _float& fAngle, const _float& fTimeDelta);// Rot-Right
	void	Rot_Yaw(const _float& fAngle, const _float& fTimeDelta);  // Rot-Up
	void	Rot_Roll(const _float& fAngle, const _float& fTimeDelta); // Rot-Look

	void	Set_Billboard(_matrix* _matView)
	{
		D3DXMatrixIdentity(&m_matBill);
		m_matBill._11 = _matView->_11;
		m_matBill._13 = _matView->_13;
		m_matBill._31 = _matView->_31;
		m_matBill._33 = _matView->_33;

		D3DXMatrixInverse(&m_matBill, 0, &m_matBill);
	}

	void			Chase_Target(const _vec3* pTargetPos, const _float& fSpeed, const _float& fTimeDelta);
	

public:
	HRESULT		Ready_Transform(void);
	virtual		_int	Update_Component(const _float& fTimeDelta);
	virtual		void	LateUpdate_Component(void);

private:
	MOVETYPE	m_eMoveType;

public:
	_vec3		m_vInfo[INFO_END];
	_vec3		m_vScale;

	_matrix		m_matWorld;
	_matrix		m_matBill;

public:
	static CTransform*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*		Clone(void);

private:
	_matrix*	Compute_Lookattarget(const _vec3* pTargetPos);
	virtual void	Free(void) override;

};
END