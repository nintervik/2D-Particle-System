#ifndef __EMITTER_H__
#define __EMITTER_H__

#include "p2Point.h"
#include "j1ParticleSystem.h"
#include "ParticlePool.h"
#include "SDL/include/SDL.h"

struct SDL_Texture;

// TODO: make an enum of Emitter types for different kind of particles

class Emitter
{
private:

	iPoint pos;
	int emissionRate = 0;
	float angle = 0.0f;
	float speed = 0.0f;
	ParticlePool emitterPool;
	j1Module* callback = nullptr; // TODO: Do we need this?
	SDL_Texture* emitter_tex = nullptr;


	// TODO: add emissionRate and other stuff from the pdf of Star Treck


	//int particlesPerFrame = 0;

public:
	bool to_destroy = false;

	//TODO: add emissionRate to constuctor

	Emitter(iPoint pos, float angle, float speed);
	void Update(float dt);
	//bool Remove();
};

#endif