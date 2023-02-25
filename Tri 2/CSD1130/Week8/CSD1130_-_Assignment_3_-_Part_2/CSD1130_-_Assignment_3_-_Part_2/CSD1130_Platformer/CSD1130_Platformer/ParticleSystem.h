#pragma once
#include "Particle.h"

#define POOL 25

class ParticleSystem
{
public:

	int EmmisionRate = 10;

	Particle MasterParticle;
	Particle ParticlePool[POOL];

	void GenerateMaster(float _lifetime, float _scale, float _speed);
	void GenerateData(Particle& p);
	void LoadParticle();
	void initParticle();
	void SpawnParticle(Particle& p_, AEVec2 pos);
	void DrawParticle(ParticleSystem& ps_);
	void FreeParticle();
};