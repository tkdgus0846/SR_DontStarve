#pragma once
#include "GameObject.h"
#include "ISaveTarget.h"
BEGIN(Engine)
class CTexture;
class CAnimation;
END

class CTile : public CGameObject, public ISaveTarget
{
protected:
	explicit CTile(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CTile();

public:
	HRESULT Ready_GameObject();
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	void CalcColliderSize();
	CCollider*	GetCollider() { return m_pCollider; }
	virtual void OnCollisionStay(const class Collision* collision);

	_bool IsBodyCollider(const Collision*& collision);

protected:
	virtual HRESULT Add_Component() override;

public:
	_vec3 NormalVectorFromTile();

protected:
	Engine::CAnimation* m_pAnimation;
	Engine::CCollider*	m_pCollider;
	//TILE_TYPE			m_eTileType;

private:
	virtual void Free(void) override;

	// ISaveTarget을(를) 통해 상속됨
	virtual void Save(HANDLE hFile, DWORD & dwByte) override;
	virtual void Load(HANDLE hFile, DWORD & dwByte) override;
};