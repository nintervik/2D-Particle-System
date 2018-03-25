#ifndef __EMITTER_H__
#define __EMITTER_H__

#include "p2Point.h"
#include "j1ParticleSystem.h"
#include "ParticlePool.h"
#include "SDL/include/SDL.h"

struct SDL_Texture;
class ParticlePool;

// TODO: make an enum of Emitter types for different kind of particles

class Emitter
{
private:

	iPoint pos = { 0, 0 };
	fPoint angleRange = { 0.0f, 360.0f };
	
	
	SDL_Texture* emitter_tex = nullptr;
	float maxSpeed = 0.0f;
	float maxSize = 0.0f;
	ParticlePool* emitterPool = nullptr;

	// ---------------------------------------------------------
	// TODO later
	j1Module* callback = nullptr; // TODO: Do we need this?
	int emissionRate = 0;

	int poolSize = 0;
	uint emitNumber = 0u;
	uint emitVariance = 0u;
	uint maxParticleLife = 0u;
	uint maxParticlesPerFrame = 0.0f;

	// TODO: add emissionRate and other stuff from the pdf of Star Treck
	//int particlesPerFrame = 0;

public:
	bool to_destroy = false;

	//TODO: add emissionRate to constuctor

	Emitter(iPoint pos, uint emitNumber, uint emitVariance, uint maxParticleLife, fPoint angleRange, float maxSpeed, float maxSize);
	virtual ~Emitter();
	
	void Update(float dt);
	void Draw(SDL_Texture* texture);
	float RangeRandomNum(float min = -1.0f, float max = 1.0f);
	int GetPoolSize() const;
};

#endif