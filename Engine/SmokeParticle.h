#pragma once
#include "ParticleSystem.h"

class CSmokeParticle : public CParticleSystem
{
public:
	explicit CSmokeParticle(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSmokeParticle(const CSmokeParticle& rhs);
	virtual ~CSmokeParticle();

	virtual void ResetParticle(Particle* particle) override;

	virtual _int Update_Component(const _float& fTimeDelta) override;


	static CSmokeParticle* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent* Clone(void) override;
};

