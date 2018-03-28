#ifndef __EMITTER_H__
#define __EMITTER_H__

#include "p2Point.h"
#include "j1ParticleSystem.h"
#include "ParticlePool.h"
#include "j1PerfTimer.h"
#include "SDL/include/SDL.h"

struct SDL_Texture;
class ParticlePool;

// TODO: make an enum of Emitter types for different kind of particles

class Emitter
{
private:

	// Particles size and movement
	iPoint pos = { 0, 0 };
	fPoint angleRange = { 0.0f, 360.0f };
	float maxSpeed = 0.0f;
	float maxSize = 0.0f;

	// Particles emission
	int emissionRate = 0;
	uint emitNumber = 0u;
	uint emitVariance = 0u;
	uint maxParticleLife = 0u;
	uint maxParticlesPerFrame = 0.0f;

	// Pool
	ParticlePool* emitterPool = nullptr;
	int poolSize = 0;

	bool active = false;
	SDL_Rect textureRect;
	j1PerfTimer emitterTimer;
	double stopTime = 0.0f;

public:

	bool toDestroy = false;

	Emitter(iPoint pos, uint emitNumber, uint emitVariance, uint maxParticleLife, fPoint angleRange, float maxSpeed, float maxSize, SDL_Rect textureRect);
	virtual ~Emitter();
	
	void Update(float dt);
	float RangeRandomNum(float min = -1.0f, float max = 1.0f);
	int GetPoolSize() const;
	void StartEmission();
	void StopEmission(double timer = 0.0f);
	void MoveEmitter(iPoint newPos);
	iPoint GetEmitterPos() const;
};

#endif