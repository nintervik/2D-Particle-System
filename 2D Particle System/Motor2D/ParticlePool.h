#ifndef __PARTICLE_POOL_H__
#define __PARTICLE_POOL_H__

#include "Particle.h"
#include "p2Point.h"

class ParticlePool
{
private:
	static const int POOL_SIZE = 100;
	Particle particles[POOL_SIZE];
	Particle* firstAvailable;

public:
	ParticlePool();
	void Generate(iPoint pos, float speed, float angle, float start_radius, uint life);
	void Update(float dt);
};

#endif