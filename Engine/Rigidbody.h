#pragma once
#include "Component.h"

BEGIN(Engine)

typedef	enum FroceMode
{
	FORCE,//���� + �������� X
	ACCELERATION, //  ���� + �������� O
	IMPULSE, //�ҿ��� + �������� X
	VELOCITYCHANGE // �ҿ��� + �������� O
}FORCEMODE;

typedef enum WorldAxis
{
	WORLDAXIS_X, //X�� 
	WORLDAXIS_Y, //Y��
	WORLDAXIS_Z  //Z��
}WORLDAXIS;

class CRigidbody :
	public CComponent
{
private:
	explicit CRigidbody(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CRigidbody(const CRigidbody& rhs);
	virtual ~CRigidbody();

public:
	//������ �ٵ� �ʱ⼳�� �Լ�.
	HRESULT Ready_Rigidbody(void);

	//������Ʈ ������Ʈ
	virtual _int Update_Component(const _float& fTimeDelta);

	//������Ʈ late������Ʈ
	virtual void LateUpdate_Component(void);

public:
	//���� ���ϴ� �Լ� //����,��,���,�ð�(���ȿ������ �����)�� �Է¹���.
	//����
	void AddForce(_vec3 _toward, _float _force, FORCEMODE _mode = FORCE, const _float & fTimeDelta=1);
	void AddForce(_vec3 _force, FORCEMODE _mode = FORCE, const _float & fTimeDelta =1);
	//����
	void AddRelativeForce(_vec3 _toward, _float _force, FORCEMODE _mode = FORCE, const _float & fTimeDelta = 1);
	void AddRelativeForce(_vec3 _force, FORCEMODE _mode = FORCE, const _float & fTimeDelta = 1);

	//ȸ���� ��Ű�� �Լ� //��,��,���,�ð�(���ȿ������ �����)�� �Է¹���.
	//����
	void AddTorque(_vec3 _axis, _float _force, FORCEMODE _mode = FORCE, const _float & fTimeDelta = 1);
	void AddTorque(_vec3 _force, FORCEMODE _mode = FORCE, const _float & fTimeDelta = 1);

public:
	/////////�̵�///////////// 
	//��
	_vec3 m_Force;
	//���� �ӵ�
	_vec3 m_Velocity;
	//�ʱ�ӵ�
	_vec3 m_InitialVelocity;
	//���ӵ�
	_vec3 m_Accele;

	//////////ȸ��///////////
	//x,y,z�� ��
	_vec3 m_AngularForce;
	//���ӵ�
	_vec3 m_AngularVelocity;
	//�����ӵ�
	_vec3 m_AngularAccele;

	////////����////////////
	//�߷� ���� (�߷��� ���� ����)
	_vec3 m_fGravity;
	//����
	_float m_fMass;
	//��������
	_float m_fAirResistance;

	////////�ɼ�///////////
	//�߷� ���� ����
	_bool m_bUseGrivaty;
	//rigidbody�� ���� ������ ��ȯ ���� ����
	_bool m_bFreezePos_X;
	_bool m_bFreezePos_Y;
	_bool m_bFreezePos_Z;
	//rigidbody�� ���� �����̼� ��ȯ ���� ����
	_bool m_bFreezeRot_X;
	_bool m_bFreezeRot_Y;
	_bool m_bFreezeRot_Z;

public:
	static CRigidbody* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free(void) override;
};

END