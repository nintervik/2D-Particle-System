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
	static const int POOL_SIZE = 6000;
	int poolSize = 0;
	Particle particles[POOL_SIZE];
	Particle* firstAvailable;
	std::vector<Particle*> particlesVec;

public:
	ParticlePool(Emitter* emitter);
	virtual ~ParticlePool();
	void Generate(iPoint pos, float speed, float angle, float start_radius, uint life);
	void Update(float dt);
};

#endif