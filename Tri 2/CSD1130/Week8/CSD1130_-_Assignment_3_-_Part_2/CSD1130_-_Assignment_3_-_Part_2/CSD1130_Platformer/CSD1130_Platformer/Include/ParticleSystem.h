#pragma once
#include "Particle.h"

#define POOL 100

class ParticleSystem
{
public:

	float EmmisionTime = 0.05f;
	Particle MasterParticle;
	Particle ParticlePool[POOL];

	void GenerateMaster(float _lifetime, float _scale, float _speed);
	void RandomSpreadData(Particle& p);
	void LoadParticle();
	void initParticle();
	void SpawnParticle(Particle& p_, AEVec2 pos);
	void FreeParticle();
};