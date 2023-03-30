#pragma once

#include "Typedef.h"

BEGIN(Engine)

typedef	 struct tagVertexColor
{
	_vec3			vPos;		// ��ġ
	_ulong			dwColor;	// ����

}VTXCOL;

const	_ulong		FVF_COL = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0;

typedef	 struct tagVertexTexture
{
	_vec3			vPos;		// ��ġ
	_vec2			vTexUV;		// ����

}VTXTEX;

const	_ulong		FVF_TEX = D3DFVF_XYZ | D3DFVF_TEX1;

typedef	 struct tagVertexCube
{
	_vec3			vPos;		// ��ġ
	_vec3			vTexUV;		// ����

}VTXCUBE;

const	_ulong		FVF_CUBE = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0);

typedef VTXCOL PTCCOL;
typedef VTXTEX PTCTEX;

// D3DFVF_TEXCOORDSIZE3 : �ؽ�ó�� UV���� FLOAT�� 3���� ũ�� ��ŭ�̸� ��ȣ �� ������ �ǹ̴� ���� ���ؽ��� UV ���� ������ ���� �� �մµ� �� �� ù ��° ���� ����ϰڴٴ� �ǹ�

typedef	struct tagIndex16
{
	_ushort		_0;
	_ushort		_1;
	_ushort		_2;

}INDEX16;

typedef	struct tagIndex32
{
	_ulong		_0;
	_ulong		_1;
	_ulong		_2;

}INDEX32;

struct Particle
{
	_vec3 vPos;
	_vec3 vVelocity;
	_vec3 vAccel;
	float fLifeTime;
	float fAge;
	_ulong dwColor;
	_ulong dwColorFade;
	bool bIsAlive;
};

struct Bound
{
	// �浹�ߴ��� �ƴ��� ���� �˻�
	virtual bool Intersect(const _vec3& point) PURE;
	// ���ӿ�����Ʈ�� �̵��Ҷ� ���� �����̰� �ϴ� �Լ�
	virtual void Offset(const _vec3& origin) PURE;
};



struct BoundingBox : public Bound
{
	enum COLDIR
	{
		COLDIR_TOP, BC_BOTTOM, BC_LEFT, BC_RIGHT
	};

	BoundingBox(const _vec3& offsetMin = { -1.f, -1.f, -1.f }, const _vec3& offsetMax = { 1.f, 1.f, 1.f })
	{
		_offsetMin = offsetMin;
		_offsetMax = offsetMax;
		_min = { 0.f,0.f,0.f };
		_max = { 0.f,0.f,0.f };
	}

	_vec3	Get_Center()
	{
		return (_max - _min) / 2 + _min;
	}

	_vec3	Get_Size()
	{
		return _offsetMax - _offsetMin;
	}

	// ������ ť��� ���� �浹��
	virtual bool Intersect(const _vec3& point) override
	{
		if (point.x >= _min.x && point.y >= _min.y && point.z >= _min.z &&
			point.x <= _max.x && point.y <= _max.y && point.z <= _max.z)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// ������ ��ġ�� �޾ƿͼ� offsetMin �̶� offsetMax��ŭ ������ �� ������ ���ӿ�����Ʈ�� ���������� ������ �޶����� �ϱ⶧��.
	virtual void Offset(const _vec3& origin) override
	{
		_min = origin + _offsetMin;
		_max = origin + _offsetMax;
	}

	// origin + ť���� ũ�� (ť�� ���� ��ǥ)
	_vec3 _min;
	_vec3 _max;

	// ť���� ũ�� (ť�� ���� ��ǥ)
	_vec3 _offsetMin;
	_vec3 _offsetMax;
};

// �̰� �浹�� ���� ������ ������� ����ü�ε� ����ٰ� ���� �������� �ε������� üũ�ϴ°� ������ �� �����Ű��ƿ�
struct Collision
{
	// � ���ӿ�����Ʈ�� �浹�ߴ���, ���� Ʈ�������� ��������,
	// � �ݶ��̴��� �浹�ߴ����� ���� ��������
	class CGameObject* otherObj;
	class CTransform* otherTrans;
	class CCollider* otherCollider;
};

typedef struct tagViewParams
{
	_vec3 vEye;
	_vec3 vAt;
	_vec3 vUp;

	tagViewParams()
	{
		ZeroMemory(this, sizeof(tagViewParams));
	}
	tagViewParams(const _vec3& vEye, const _vec3& vAt, const _vec3& vUp)
	{
		this->vEye = vEye;
		this->vAt = vAt;
		this->vUp = vUp;
	}
	tagViewParams(const tagViewParams& rhs)
	{
		this->vEye = rhs.vEye;
		this->vAt = rhs.vAt;
		this->vUp = rhs.vUp;
	}
	D3DXMATRIX* LookAtLH(D3DXMATRIX* pMatView)
	{
		return D3DXMatrixLookAtLH(pMatView, &vEye, &vAt, &vUp);
	}
}VIEWPARAMS;

typedef struct tagProjParams
{
	_float fFov;
	_float fAspect;
	_float fNear;
	_float fFar;

	tagProjParams()
	{
		ZeroMemory(this, sizeof(tagProjParams));
	}
	tagProjParams(const _float& fFov, const _float& fAspect, const _float& fNear, const _float& fFar)
	{
		this->fFov = fFov;
		this->fAspect = fAspect;
		this->fNear = fNear;
		this->fFar = fFar;
	}
	tagProjParams(const tagProjParams& rhs)
	{
		this->fFov = rhs.fFov;
		this->fAspect = rhs.fAspect;
		this->fNear = rhs.fNear;
		this->fFar = rhs.fFar;
	}
	D3DXMATRIX* PerspectiveLH(D3DXMATRIX* pMatProj)
	{
		return D3DXMatrixPerspectiveFovLH(pMatProj, fFov, fAspect, fNear, fFar);
	}
}PROJPARAMS;

END