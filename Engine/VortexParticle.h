#pragma once
#include "ParticleSystem.h"

BEGIN(Engine)
class  CVortexParticle : public CParticleSystem
{
public:
	explicit CVortexParticle(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CVortexParticle(const CVortexParticle& rhs);
	virtual ~CVortexParticle();

	virtual void ResetParticle(Particle* particle) override;

	virtual _int Update_Component(const _float& fTimeDelta) override;


	static CVortexParticle* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent* Clone(void) override;

private:
	_float m_fRadius;

private:
	virtual void PreRender() override;
	virtual void PostRender() override;

protected:
	virtual void Free(void) override;
};
END

