#pragma once
#include "AEEngine.h"

class Particle
{
public:

	AEVec2 ParticleVec;
	AEGfxVertexList* pMesh;
	AEVec2 scale;
	float speed;
	float rotation;

	float lifetime;
	bool is_Alive;

	Particle& operator=(const Particle&);
};