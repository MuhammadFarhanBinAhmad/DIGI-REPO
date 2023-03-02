#include "Particle.h"

Particle& Particle::operator=(const Particle& p)
{
	this->ParticleVec = p.ParticleVec;
	this->lifetime = p.lifetime;
	this->speed = p.speed;
	this->scale = p.scale;
	this->is_Alive = p.is_Alive;

	return *this;
}