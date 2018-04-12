#include "ParticlePool.h"
#include <assert.h>


#include "Brofiler\Brofiler.h"


// This pool constructor sets our particles to available
ParticlePool::ParticlePool(Emitter* emitter)
{
	// Fill the pool according to poolSize needed for the emitter
	poolSize = emitter->GetPoolSize();
	particleArray = new Particle[poolSize];

	// The first particle is available
	firstAvailable = &particleArray[0];

	// Each particle points to the next one
	for (int i = 0; i < poolSize - 1; i++)
		particleArray[i].SetNext(&particleArray[i + 1]);

	// The last particle points to nullptr indicating the end of the vector
	particleArray[poolSize - 1].SetNext(nullptr);
}

ParticlePool::~ParticlePool()
{
	delete[] particleArray;
	particleArray = nullptr;
}

void ParticlePool::Generate(fPoint pos, float startSpeed, float endSpeed, float angle, float rotSpeed, float startSize, float endSize, uint life, SDL_Rect textureRect, SDL_Color startColor, SDL_Color endColor, SDL_BlendMode blendMode)
{
	// Check if the pool is not full
	assert(firstAvailable != nullptr);

	// Remove it from the available list
	Particle* newParticle = firstAvailable;
	firstAvailable = newParticle->GetNext();

	// Initialize new alive particle
	newParticle->Init(pos, startSpeed, endSpeed, angle, rotSpeed, startSize, endSize, life, textureRect, startColor, endColor, blendMode);
}

bool ParticlePool::Update(float dt)
{
	bool ret = false;

	BROFILER_CATEGORY("Pool update", Profiler::Color::LightCyan)
	for (int i = 0; i < poolSize; i++)
	{
		if (particleArray[i].IsAlive())
		{
			
			particleArray[i].Update(dt);
			particleArray[i].Draw();
			ret = true;
		}
		else // if a particle dies it becomes the first available in the pool
		{
			// Add this particle to the front of the vector
			particleArray[i].SetNext(firstAvailable);
			firstAvailable = &particleArray[i];
		}
	}

	return ret;
}