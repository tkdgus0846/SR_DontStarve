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

	// �ε� �������� ���� ��ü�鿡���� ������Ʈ�� �����ϸ� �ȵǱ� ������ ���� ���̾�� ���� �������̾�鸸 ������Ʈ�Ҽ� �ְ� �����.
	

	virtual void		LateUpdate_Scene(void)override;
	virtual void		Render_Scene(void) override;

	void				Set_Stage(CScene* stageScene)
	{
		m_pScene = stageScene;
	}

	void				Set_LoadingID(LOADINGID loadingID)
	{
		m_eLoadingID = loadingID;
	}

private:
	HRESULT				Ready_Proto(void);

private:
	class CLoading*			m_pLoading;

	CScene*					m_pScene;
	class CMiniGame*		m_pMiniGame;

	_bool					m_bLoadingCreated;
	LOADINGID				m_eLoadingID;

public:
	static CLoadingScene*		Create(LPDIRECT3DDEVICE9 pGraphicDev, LOADINGID loadingID, CScene* stageScene = nullptr);

private:
	virtual void		Free(void);
};

