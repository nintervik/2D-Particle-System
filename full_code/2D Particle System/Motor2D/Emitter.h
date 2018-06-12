#ifndef __EMITTER_H__
#define __EMITTER_H__

#include "p2Point.h"
#include "j1ParticleSystem.h"
#include "ParticlePool.h"
#include "j1PerfTimer.h"
#include "SDL/include/SDL.h"

struct SDL_Texture;
class ParticlePool;
struct EmitterData;

class Emitter
{
private:

	// Particles size and movement
	fPoint pos = { 0.0f, 0.0f };
	fPoint angleRange = { 0.0f, 360.0f };
	float startSpeed = 0.0f;
	float endSpeed = 0.0f;
	float startSize = 0.0f;
	float endSize = 0.0f;
	double rotSpeed = 0;

	// Particles emission
	int emissionRate = 0;
	uint emitNumber = 0u;
	uint emitVariance = 0u;
	uint maxParticleLife = 0u;
	uint maxParticlesPerFrame = 0u;

	// Pool
	ParticlePool* emitterPool = nullptr;
	int poolSize = 0;

	// Emission time
	j1PerfTimer stopTimer;
	j1PerfTimer emissionTimer;
	j1PerfTimer lifeTimer;
	double stopTime = 0.0f;
	double emissionTime = 0.0f;
	double lifetime = -1.0f;
	bool active = false;

	// Color and render properties
	SDL_Color startColor = { 0, 0, 0, 0 };
	SDL_Color endColor = { 0, 0, 0, 0 };
	SDL_Rect textureRect;
	SDL_BlendMode blendMode = SDL_BlendMode::SDL_BLENDMODE_NONE;
	float timeStep = 0.0f;

	// Random control parameters
	fPoint rotSpeedRand = { 0.0f, 0.0f };
	fPoint startSpeedRand = { 0.0f, 0.0f };
	fPoint endSpeedRand = { 0.0f, 0.0f };
	fPoint emitVarianceRand = { 0.0f, 0.0f };
	fPoint lifeRand = { 0.0f, 0.0f };
	fPoint startSizeRand = { 0.0f, 0.0f };
	fPoint endSizeRand = { 0.0f, 0.0f };

	// Vortex control parameters
	bool vortexSensitive = false;

public:

	Emitter(fPoint pos, EmitterData data);
	// fPoint pos, uint emitNumber, uint emitVariance, uint maxParticleLife, fPoint angleRange, double rotSpeed, float maxSpeed, float startSize, float endSize, SDL_Rect textureRect, SDL_Color startColor = { 0, 0, 0, 0 }, SDL_Color endColor = { 0, 0, 0, 0 }, SDL_BlendMode blendMode = SDL_BlendMode::SDL_BLENDMODE_NONE, double lifetime = -1.0f
	virtual ~Emitter();

	void Update(float dt);
	bool Draw(float dt);

	// Generates random number between given range
	float RangeRandomNum(float min = -1.0f, float max = 1.0f);

	// Returns emitter pool size
	int GetPoolSize() const;

	// Starts emission specified by timer, if not emission time is infinite
	void StartEmission(double timer = -1.0f);

	// Stops emission specified by timer, if not emission stop time is infinite
	void StopEmission(double timer = 0.0f);

	// Emitter move methods
	void MoveEmitter(fPoint newPos);
	fPoint GetEmitterPos() const;

	void VortexSensitive(bool sensitive);
};

#endif