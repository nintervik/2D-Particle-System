#ifndef __PARTICLE_POOL_H__
#define __PARTICLE_POOL_H__

#include "Particle.h"
#include "Emitter.h"
#include "p2Point.h"
#include <vector>

class Emitter;

class ParticlePool
{
private:
	static const int POOL_SIZE = 100;
	int poolSize = 0;
	Particle particles[POOL_SIZE];
	std::vector<Particle> particles_vec;
	Particle* firstAvailable;

public:
	ParticlePool(Emitter* emitter);
	void Generate(iPoint pos, float speed, float angle, float start_radius, uint life);
	void Update(float dt);
};

#endif