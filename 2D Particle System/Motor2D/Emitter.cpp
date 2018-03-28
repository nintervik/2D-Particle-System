#include "Emitter.h"
#include <time.h>


Emitter::Emitter(iPoint pos, uint emitNumber, uint emitVariance, uint maxParticleLife, fPoint angleRange, float maxSpeed, float maxSize, SDL_Rect textureRect, double lifeTime)
{ 
	srand(time(NULL));
	
	this->angleRange = angleRange;
	this->maxSpeed = maxSpeed;
	this->maxSize = maxSize;
	this->pos = pos;

	// Particle emission calculations
	this->emitNumber = emitNumber;
	this->emitVariance = emitVariance;
	this->maxParticleLife = maxParticleLife;
	maxParticlesPerFrame = emitNumber + emitVariance;

	// Particles pool 
	poolSize = maxParticlesPerFrame * (maxParticleLife + 1);
	
	emitterPool = new ParticlePool(this);

	active = true;
	this->textureRect = textureRect;
	this->lifeTime = lifeTime;

	if (this->lifeTime != -1.0f && this->lifeTime > 0.0f)
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
		float randSpeed = maxSpeed * RangeRandomNum(0.0f, 1.0f);
		float randAngle = RangeRandomNum(angleRange.x, angleRange.y);
		float randRadius = maxSize * RangeRandomNum(0.0f, 1.0f);

		// TODO: do a for loop according to emisionRate to generate as many particles as needed
		// This calculations should be float and then ceil

		// Particle generation from pool

		emissionRate = emitNumber + emitVariance * RangeRandomNum();

		for (int i = 0; i <= emissionRate; i++)
			emitterPool->Generate(pos, randSpeed, randAngle, randRadius, maxParticleLife, textureRect);
	}
	
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

	if (lifeTime > 0.0f)
	{
		if (lifeTimer.ReadMs() >= lifeTime)
		{
			active = false;
			lifeTime = 0.0f;
		}
	}

	// Updating particles in the pool
	if (!emitterPool->Update(dt) && lifeTime == 0.0f)
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

void Emitter::MoveEmitter(iPoint newPos)
{
	pos = newPos;
}

iPoint Emitter::GetEmitterPos() const
{
	return pos;
}
