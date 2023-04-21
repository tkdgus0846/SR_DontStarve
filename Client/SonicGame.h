#pragma once
#include "MiniGame.h"

class CSonicGame : public CMiniGame
{
private:
	explicit CSonicGame(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSonicGame();


public:
	virtual HRESULT Ready_Scene(void) override;
	virtual void Render_Scene(void) override;

	static CSonicGame*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void Free(void) override;

};

