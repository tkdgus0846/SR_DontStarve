#pragma once
#include "Scene.h"

class CStage2 : public CScene
{
private:
	explicit CStage2(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CStage2();

public:
	// CScene��(��) ���� ��ӵ�
	virtual HRESULT		Ready_Scene(void) override;
	virtual _int		Update_Scene(const _float& fTimeDelta)override;
	virtual void		LateUpdate_Scene(void)override;
	virtual void		Render_Scene(void) override;

private:
	_int				m_iCurRoomIdx;
	_int				m_iPreRoomIdx;

public:
	static CStage2*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free(void);
};

