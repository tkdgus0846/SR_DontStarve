#pragma once
#include "Monster.h"

BEGIN(Engine)

class CAnimation;

END

class CSellItem;

class CShopNpc : public CMonster
{
public:
	CShopNpc(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CShopNpc();

public:
	virtual HRESULT Add_Component() override;
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	virtual void Get_Damaged(_int Damage) override;

private:
	D3DXMATRIX  matWorld, matView;
	virtual void OnCollisionEnter(const class Collision* collsion) final;
	virtual void OnCollisionStay(const class Collision* collision) final;

	CAnimation* Ani;
	vector<CSellItem*> m_ItemList;

public:
	static CGameObject*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"ShopNpc"; }

private:
	virtual void Free(void) override;
protected:
	virtual void Serialization(HANDLE hFile, DWORD & dwByte) override;

	virtual void Deserialization(HANDLE hFile, DWORD & dwByte) override;

};

