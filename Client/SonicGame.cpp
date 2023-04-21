#include "SonicGame.h"
#include "Sonic.h"

CSonicGame::CSonicGame(LPDIRECT3DDEVICE9 pGraphicDev) :
	CMiniGame(pGraphicDev)
{

}

CSonicGame::~CSonicGame()
{
}

HRESULT CSonicGame::Ready_Scene(void)
{
	Add_GameObject(CSonic::Create(m_pGraphicDev));
	return S_OK;
}

void CSonicGame::Render_Scene(void)
{
}

CSonicGame* CSonicGame::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSonicGame *	pInstance = new CSonicGame(pGraphicDev);

	if (FAILED(pInstance->Ready_Scene()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CSonicGame::Free(void)
{
	__super::Free();
}
