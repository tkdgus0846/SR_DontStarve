#pragma once

#include "Base.h"
#include "GameObject.h"

BEGIN(Engine)


class  CLayer : public CBase
{
private:
	explicit CLayer();
	virtual ~CLayer();

public:
	CComponent*			Get_Component(const _tchar* pObjTag, const _tchar* pComponentTag, COMPONENTID eID);

public:
	HRESULT				Add_GameObject(const _tchar* pObjTag, CGameObject* pGameObject);
	/*CGameObject*		Get_GameObject(const _tchar* pObjTag); */

	HRESULT				Ready_Layer(void);
	_int				Update_Layer(const _float& fTimeDelta);
	void				LateUpdate_Layer(void);

private:
	// �̸� �ߺ��� ���������ϱ� �̷����ϸ� �̸��ߺ� ���� ������ ������ ���� �ĺ����� ��� ã�ƿ��� ���Ѵ�.
	multimap<const _tchar*, CGameObject*>			m_uMapObject;

public:
	static CLayer*		Create(void);

private:
	virtual void Free(void);

};

END