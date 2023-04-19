#pragma once
#include "Scene.h"
class CLoadingScene : public CScene
{
private:
	explicit CLoadingScene(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CLoadingScene();

public:
	// CScene��(��) ���� ��ӵ�
	virtual HRESULT		Ready_Scene(void) override;
	virtual _int		Update_Scene(const _float& fTimeDelta)override;
	virtual void		LateUpdate_Scene(void)override;
	virtual void		Render_Scene(void) override;

private:
	HRESULT				Ready_Proto(void);

private:
	class CLoading*			m_pLoading;
	class CBackGround*      m_pBackGround;

	_bool					m_bLoadingCreated;

public:
	static CLoadingScene*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free(void);
};

