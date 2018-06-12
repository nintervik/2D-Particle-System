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
	Particle* particleArray = nullptr;

public:

	ParticlePool(Emitter* emitter);
	virtual ~ParticlePool();

	//Generates a new particle each time it's called
	void Generate(fPoint pos, float startSpeed, float endSpeed, float angle, float rotSpeed, float startSize, float endSize, uint life, SDL_Rect textureRect, SDL_Color startColor, SDL_Color endColor, SDL_BlendMode blendMode, bool vortexSensitive);
	
	// Update (move and draw) particles in the pool.
	// IMPORTANT NOTE: This method returns:
	//		- true(1): if particle are still alive and have been drawn succesfully
	//      - false(0):  if particles are alive and have NOT been drawn succesfully
	//		- -1: if particles are no longer alive

	int Update(float dt);
};

#endif