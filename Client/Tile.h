#pragma once
#include "GameObject.h"

BEGIN(Engine)
class CTexture;
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
	CCollider*	GetCollider() { return m_pCollider; }

	_vec3	NormalVectorFromTile();

private:
	virtual HRESULT Add_Component() override;
	HRESULT Remove_TextureCom();

public:
	void Change_Texture(const _tchar* pTextureName);

private:
	_tchar		m_pTextureName[64];
	Engine::CTexture*	m_pTextureCom;
	Engine::CCollider*	m_pCollider;
	_int				m_iTileOption;

public:
	static CTile* Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 vPos, 
		const _tchar* pTextureName);

private:
	virtual void Free(void) override;
};