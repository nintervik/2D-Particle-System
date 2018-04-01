#ifndef __EMITTER_H__
#define __EMITTER_H__

#include "p2Point.h"
#include "j1ParticleSystem.h"
#include "ParticlePool.h"
#include "j1PerfTimer.h"
#include "SDL/include/SDL.h"

struct SDL_Texture;
class ParticlePool;

enum EmitterType
{
	EMITTER_TYPE_NONE = -1,
	EMITTER_TYPE_FIRE,
	EMITTER_TYPE_FIRE2,
};

class Emitter
{
private:

	// Particles size and movement
	fPoint pos = { 0.0f, 0.0f };
	fPoint angleRange = { 0.0f, 360.0f };
	float maxSpeed = 0.0f;
	float maxSize = 0.0f;

	// Particles emission
	int emissionRate = 0;
	uint emitNumber = 0u;
	uint emitVariance = 0u;
	uint maxParticleLife = 0u;

	uint maxParticlesPerFrame = 0u;

	// Pool
	ParticlePool* emitterPool = nullptr;
	int poolSize = 0;

	bool active = false;
	SDL_Rect textureRect;
	j1PerfTimer stopTimer;
	j1PerfTimer emissionTimer;
	j1PerfTimer lifeTimer;
	double stopTime = 0.0f;
	double emissionTime = 0.0f;
	double lifetime = -1.0f;
	EmitterType type = EmitterType::EMITTER_TYPE_NONE;

public:

	bool toDestroy = false;

	Emitter(fPoint pos, uint emitNumber, uint emitVariance, uint maxParticleLife, fPoint angleRange, float maxSpeed, float maxSize, SDL_Rect textureRect, double lifetime = -1.0f);
	virtual ~Emitter();
	
	void Update(float dt);
	float RangeRandomNum(float min = -1.0f, float max = 1.0f);
	int GetPoolSize() const;
	void StartEmission(double timer = -1.0f);
	void StopEmission(double timer = 0.0f);
	void MoveEmitter(fPoint newPos);
	fPoint GetEmitterPos() const;
};

#endif