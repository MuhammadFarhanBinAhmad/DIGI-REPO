#include "ParticleSystem.h"
#include "RenderingSystem.h"
#include "main.h"

/****************************************************************************** /
/*!
\file   ParticleSystem.cpp
\author Muhammad Farhan Bin Ahmad(2200544)
\brief
  A script does the following:
	GenerateMaster - Generate a master copy for particle to refer to
	GenerateData - Particle get data from the Master particle but also generate their own random data(rotation)
	LoadParticle - Create mesh for particle
	initParticle - Initialize default value for all particle at the start
	SpawnParticle - Spawn particle at desire location and move particle
	FreeParticle - Free particle mesh
*/
/******************************************************************************/



void ParticleSystem::GenerateMaster(float _lifetime, float _scale, float _speed)
{
	//Gemerate master copy for particle to copy
	AEVec2 Sc;
	Sc.x = _scale;
	Sc.y = _scale;
	MasterParticle.lifetime = _lifetime;
	MasterParticle.scale = Sc;
	MasterParticle.speed = _speed;
}

void ParticleSystem::RandomSpreadData(Particle& p)
{
	//Fixed value
	p.lifetime = MasterParticle.lifetime;
	p.scale = MasterParticle.scale;
	p.speed = MasterParticle.speed;
	p.pMesh = MasterParticle.pMesh;

	//Random value
	p.rotation = 0 + 6 * AERandFloat();
	//Set direction for particle to move
	AEVec2 dirvec = { 0,1 };//Direction vector of ship
	AEVec2Add(&p.ParticleVec, &p.ParticleVec, &dirvec);//Move player foward

	p.is_Alive = false;
}

void ParticleSystem::LoadParticle()
{

	AEGfxMeshStart();

	AEGfxTriAdd(
		-0.5f, 0.5f, 0xFFFFFFFF, 0.f, 0.f,
		-0.5f, -0.5f, 0xFFFFFFFF, 0.f, 0.f,
		0.5f, 0.5f, 0xFFFFFFFF, 0.f, 0.f);
	AEGfxTriAdd(
		0.5f, 0.5f, 0xFFFFFFFF, 0.f, 0.f,
		-0.5f, -0.5f, 0xFFFFFFFF, 0.f, 0.f,
		0.5f, -0.5f, 0xFFFFFFFF, 0.f, 0.f);

	MasterParticle.pMesh = AEGfxMeshEnd();

}
void ParticleSystem::initParticle()
{
	//Initialize value for all particle
	for (int i = 0; i < POOL; i++)
	{
		ParticlePool[i].lifetime = MasterParticle.lifetime;
		ParticlePool[i].scale = MasterParticle.scale;
		ParticlePool[i].speed = MasterParticle.speed;
	}
}

void ParticleSystem::SpawnParticle(Particle& p_, AEVec2 pos)
{
	//Spawn and move particle
	p_.is_Alive = true;
	p_.ParticleVec = pos;
	printf("par: %f", p_.ParticleVec.x);
	RenderEntity(p_ , p_.pMesh);



}
void ParticleSystem::FreeParticle()
{
	AEGfxMeshFree(MasterParticle.pMesh);
}