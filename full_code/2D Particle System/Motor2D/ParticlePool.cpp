#include "ParticlePool.h"
#include <assert.h>


#include "Brofiler\Brofiler.h"


// This pool constructor sets our particles to available
ParticlePool::ParticlePool(Emitter* emitter)
{
	/* TODO 2.2: Convert particleArray into a free list:
	- Make the firstAvailable pointer point to the first element of the pool
	- Make each particle inside the pool point to the next one. Use the SetNext() method
	- Make the last particle point to nullptr
	*/

	/* TODO 3.2 - Allocate memory for the pool:
	- Use GetPoolSize() from the given emitter.
	- Remember to free the memory!
	*/

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
	/* TODO 2.3 Generate a new particle from the pool
	- Use firstAvailable to Init the particle.
	- But remember to move the firstAvailable pointer to the next particles so we don't lose track of it.
	- Also check first that the pool is not empty befor doing anything. Use assert for this.
	*/

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
	/* TODO 2.4 Update and draw living particles in the pool.
	- If it's alive update it, draw it and make sure to return true
	- If a particle is dead it becomes the first available in the pool.
	Use IsAlive() method to check this.
	*/

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