#include "Emitter.h"
#include <time.h>


Emitter::Emitter(fPoint pos, uint emitNumber, uint emitVariance, uint maxParticleLife, fPoint angleRange, float maxSpeed, float startSize, float endSize, SDL_Rect textureRect, SDL_Color startColor, SDL_Color endColor, SDL_BlendMode blendMode, double lifeTime)
{ 
	srand(time(NULL));
	
	this->angleRange = angleRange;
	this->maxSpeed = maxSpeed;
	this->startSize = startSize;
	this->endSize = endSize;
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
	this->lifetime = lifeTime;

	this->startColor = startColor;
	this->endColor = endColor;
	this->blendMode = blendMode;

	timeStep = 1.0f / (float)maxParticleLife;

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
			emitterPool->Generate(pos, randSpeed, randAngle, randRadius, endSize, maxParticleLife, textureRect, startColor, endColor, blendMode);
			timeStep += timeStep;
		}
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

	if (lifetime > 0.0f)
	{
		if (lifeTimer.ReadMs() >= lifetime)
		{
			active = false;
			lifetime = 0.0f;
		}
	}

	// Updating particles in the pool
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