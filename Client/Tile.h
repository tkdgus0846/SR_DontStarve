#pragma once
#include "GameObject.h"

BEGIN(Engine)
class CTexture;
class CAnimation;
END

class CTile : public CGameObject
{
private:
	explicit CTile(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CTile();

public:
	HRESULT Ready_GameObject(const _tchar* pTextureName);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;
	void WriteTextureName(HANDLE hFile, DWORD& dwByte);
	void ReadTextureName(HANDLE hFile, DWORD& dwByte);
	void CalcColliderSize();
	CCollider*	GetCollider() { return m_pCollider; }
	
	//virtual void OnCollisionEnter(const class Collision* collsion);
	virtual void OnCollisionStay(const class Collision* collision);
	//virtual void OnCollisionExit(const class Collision* collision);

private:
	virtual HRESULT Add_Component() override;
	HRESULT Remove_TextureCom();

	// 타일타입은 Change_Texture로만 바꾸게 private.
	void	Set_TileType(const _tchar * pTextureName);
public:
	void Change_Texture(const _tchar* pTextureName);
	_vec3 NormalVectorFromTile();

private:
	_tchar		m_pTextureName[64];
	Engine::CAnimation* m_pAnimation;
	Engine::CTexture*	m_pTextureCom;
	Engine::CCollider*	m_pCollider;
	TILE_TYPE			m_eTileType;

public:
	static CTile* Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 vPos, 
		const _tchar* pTextureName);

private:
	virtual void Free(void) override;
};