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
	
	int poolSize = 0;
	Particle* firstAvailable;
	std::vector<Particle*> particlesVec;
	Particle* particleArray = nullptr;

public:

	ParticlePool(Emitter* emitter);
	virtual ~ParticlePool();

	void Generate(fPoint pos, float speed, float angle, float start_radius, uint life, SDL_Rect textureRect);
	bool Update(float dt);
};

#endif