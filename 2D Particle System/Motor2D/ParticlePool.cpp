#include "ParticlePool.h"
#include <assert.h>


// This pool constructor sets our particles to available
ParticlePool::ParticlePool(Emitter* emitter)
{
	// Fill the pool according to poolSize needed for the emitter

	poolSize = emitter->GetPoolSize();

	for (int i = 0; i < poolSize; i++)
		particlesVec.push_back(new Particle());

	particlesVec.shrink_to_fit();

	// The first particle is available
	firstAvailable = particlesVec[0];

	// Each particle points to the next one
	for (int i = 0; i < poolSize - 1; i++)
		particlesVec[i]->SetNext(particlesVec[i + 1]);

	// The last particles points to nullptr indicating the end of the list
	particlesVec[poolSize - 1]->SetNext(nullptr);

	// --- Original code
	/*
	// The first particle is available
	firstAvailable = &particles[0];

	// Each particle points to the next one
	for (int i = 0; i < POOL_SIZE - 1; i++)
	{
		particles[i].SetNext(&particles[i + 1]);
	}

	// The last particles points to nullptr indicating the end of the list
	particles[POOL_SIZE - 1].SetNext(nullptr);

	*/

}

ParticlePool::~ParticlePool()
{
	std::vector<Particle*>::const_iterator it_particle = this->particlesVec.begin();

	while (it_particle != this->particlesVec.end()) 
	{
		delete *it_particle;
		it_particle++;
	}

	particlesVec.clear();
}

void ParticlePool::Generate(iPoint pos, float speed, float angle, float start_radius, uint life)
{
	// Check if the pool is not full
	assert(firstAvailable != nullptr);

	// Remove it from the available list
	Particle* newParticle = firstAvailable;
	firstAvailable = newParticle->GetNext();

	newParticle->Init(pos, speed, angle, start_radius, life);
}

void ParticlePool::Update(float dt)
{
	for (int i = 0; i < poolSize; i++)
	{
		if (particlesVec[i]->IsAlive())
		{
			particlesVec[i]->Update(dt);
			particlesVec[i]->Draw();
		}
		else // if a particle dies it becomes the first available one in the pool
		{
			// Add this particle to the front of the vector
			particlesVec[i]->SetNext(firstAvailable);
			firstAvailable = particlesVec[i];
		}
	}

	// Original code
	/*
	for (int i = 0; i < POOL_SIZE; i++)
	{
		if (particles[i].IsAlive())
		{
			particles[i].Update(dt);
			particles[i].Draw();
		}
		else // if a particle dies it becomes the first available one in the pool
		{
			// Add this particle to the front of the list
			particles[i].SetNext(firstAvailable);
			firstAvailable = &particles[i];
		}
	}
	*/
}