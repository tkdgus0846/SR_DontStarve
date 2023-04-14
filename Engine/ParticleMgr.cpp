#include "stdafx.h"
#include "ParticleMgr.h"

IMPLEMENT_SINGLETON(CParticleMgr)

CParticlePool::CParticlePool()
{
}

CParticlePool::~CParticlePool()
{
}

void CParticlePool::Push(CParticle* pObj)
{
	if (nullptr == pObj)
		return;

	m_ParticlePool.push_back(pObj);
}

CParticle * CParticlePool::Pop(LPDIRECT3DDEVICE9 pDevice, const _tchar* ParticleName, _int ParticleNum, const _vec3& vPos, const _vec3& Origin)
{
	CParticle*		pParticle = nullptr;

	if (m_ParticlePool.empty())
	{
		pParticle = CParticle::Create(pDevice, ParticleName, ParticleNum, vPos, Origin);
		++m_iCreateCnt;
	}
	else
	{
		pParticle = m_ParticlePool.front();
		m_ParticlePool.pop_front();
	}

	if (nullptr == pParticle)
		return nullptr;

	(pParticle)->Set_Pos(vPos);
	(pParticle)->Reset();
	(pParticle)->SetDead(false);
	return pParticle;
}

CParticlePool* CParticlePool::Create()
{
	CParticlePool*		pInstance = new CParticlePool();
	return pInstance;
}

void CParticlePool::Free(void)
{
	for_each(m_ParticlePool.begin(), m_ParticlePool.end(), CDeleteObj());
	m_ParticlePool.clear();
}

//////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

CParticleMgr::CParticleMgr()
{

}

CParticleMgr::~CParticleMgr()
{
	Free();
}

CParticle * CParticleMgr::Pop(LPDIRECT3DDEVICE9 pDevice, const _tchar* ParticleName, _int ParticleNum, const _vec3& vPos, const _vec3& Origin)
{
	if (m_ParticlePool[ParticleName] == nullptr)
	{
		m_ParticlePool[ParticleName] = CParticlePool::Create();
	}
	CParticle*		pParticle = m_ParticlePool[ParticleName]->Pop(pDevice, ParticleName, ParticleNum, vPos, Origin);
	if (pParticle == nullptr)
		return nullptr;

	return pParticle;
}


void CParticleMgr::Push(const _tchar* name, CParticle* pParticle)
{
	if (m_ParticlePool[name] == nullptr) return;

	m_ParticlePool[name]->Push(pParticle);
}

void CParticleMgr::Free(void)
{
	for_each(m_ParticlePool.begin(), m_ParticlePool.end(), CDeleteMap());
	m_ParticlePool.clear();
}
