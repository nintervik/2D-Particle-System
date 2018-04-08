#include "Emitter.h"
#include <time.h>


Emitter::Emitter(fPoint pos, uint emitNumber, uint emitVariance, uint maxParticleLife, fPoint angleRange, double rotSpeed, float maxSpeed, float startSize, float endSize, SDL_Rect textureRect, SDL_Color startColor, SDL_Color endColor, SDL_BlendMode blendMode, double lifeTime)
{ 
	srand(time(NULL));
	
	// Particles size and movement
	this->angleRange = angleRange;
	this->maxSpeed = maxSpeed;
	this->startSize = startSize;
	this->endSize = endSize;
	this->pos = pos;
	this->rotSpeed = rotSpeed;

	// Particle emission calculations
	this->emitNumber = emitNumber;
	this->emitVariance = emitVariance;
	this->maxParticleLife = maxParticleLife;
	maxParticlesPerFrame = emitNumber + emitVariance;

	// Pool size calculations
	poolSize = maxParticlesPerFrame * (maxParticleLife + 1);
	emitterPool = new ParticlePool(this);

	// Color and render properties
	this->textureRect = textureRect;
	this->startColor = startColor;
	this->endColor = endColor;
	this->blendMode = blendMode;
	timeStep = 1.0f / (float)maxParticleLife;

	// Emission properties
	active = true;
	this->lifetime = lifeTime;

	if (this->lifetime != -1.0f && this->lifetime > 0.0f)
		lifeTimer.Start();
}

Emitter::~Emitter()
{
	delete emitterPool;
	emitterPool = nullptr;
}

void Emitter::Update(float dt)
{
	if (active)
	{
		// Particle generation from pool
		
		emissionRate = (int)(emitNumber + emitVariance * RangeRandomNum());

		for (int i = 1; i <= emissionRate; i++)
		{
			float randSpeed = maxSpeed * RangeRandomNum(0.0f, 1.0f);
			float randAngle = RangeRandomNum(angleRange.x, angleRange.y);
			float randRadius = startSize * RangeRandomNum(0.0f, 1.0f);
			double randRotSpeed = rotSpeed * RangeRandomNum();
			emitterPool->Generate(pos, randSpeed, randAngle, randRotSpeed, randRadius, endSize, maxParticleLife, textureRect, startColor, endColor, blendMode);
			timeStep += timeStep;
		}
	}

	// Emission timing calculations
	
	if (stopTime > 0.0f && !active)
	{
		emissionTime = 0.0f;
		if (stopTimer.ReadMs() >= stopTime)
		{
			active = true;
			stopTime = 0.0f;
		}
	}
	
	if (emissionTime > 0.0f)
	{
		stopTime = 0.0f;
		if (emissionTimer.ReadMs() >= emissionTime)
		{
			active = false;
			emissionTime = 0.0f;
		}
	}

	if (lifetime > 0.0f)
	{
		if (lifeTimer.ReadMs() >= lifetime)
		{
			active = false;
			lifetime = 0.0f;
		}
	}

	// Updating particles in the pool
	/* NOTE: if lifetime is 0 and last particles have been updated
	then the emitter is automatically destroyed */
	if (!emitterPool->Update(dt) && lifetime == 0.0f)
		toDestroy = true;
}

float Emitter::RangeRandomNum(float min, float max)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = max - min;
	float r = random * diff;

	return min + r;
}

int Emitter::GetPoolSize() const
{
	return poolSize;
}

void Emitter::StartEmission(double timer)
{
	if (!active)
	{
		active = true;
		emissionTime = timer;
		emissionTimer.Start();
	}
}

void Emitter::StopEmission(double timer)
{
	if (active)
	{
		active = false;
		stopTime = timer;
		stopTimer.Start();
	}
}

void Emitter::MoveEmitter(fPoint newPos)
{
	pos = newPos;
}

fPoint Emitter::GetEmitterPos() const
{
	return pos;
}