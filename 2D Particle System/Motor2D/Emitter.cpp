#include "Emitter.h"
#include <time.h>


Emitter::Emitter(iPoint pos, uint emitNumber, uint emitVariance, uint maxParticleLife, fPoint angleRange, float maxSpeed, float maxSize)
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
	poolSize = maxParticlesPerFrame * maxParticleLife;
	emitterPool = new ParticlePool(this);

	active = true;
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
			emitterPool->Generate(pos, randSpeed, randAngle, randRadius, maxParticleLife);
	}

	// Updating particles in the pool
	emitterPool->Update(dt);
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

void Emitter::StartEmission()
{
	active = true;
}

void Emitter::StopEmission()
{
	active = false;
}

void Emitter::MoveEmitter(iPoint newPos)
{
	pos = newPos;
}

iPoint Emitter::GetEmitterPos() const
{
	return pos;
}
