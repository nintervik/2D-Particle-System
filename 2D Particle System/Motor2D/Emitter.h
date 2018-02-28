#ifndef __EMITTER_H__
#define __EMITTER_H__

#include "p2Point.h"
#include "ParticlePool.h"

// TODO: make an enum of Emitter types for different kind of particles

class Emitter
{
private:

	iPoint pos;
	int emissionRate = 0;
	float angle = 0.0f;
	float speed = 0.0f;
	ParticlePool emitterPool;

	//int particlesPerFrame = 0;

public:

	//TODO: add emissionRate to constuctor

	Emitter(iPoint pos, float angle, float speed);
	void Update(float dt);
	//bool Remove();
};

#endif