#include "ParticlePool.h"
#include <assert.h>


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
}

ParticlePool::~ParticlePool()
{

}

void ParticlePool::Generate(fPoint pos, float startSpeed, float endSpeed, float angle, float rotSpeed, float startSize, float endSize, uint life, SDL_Rect textureRect, SDL_Color startColor, SDL_Color endColor, SDL_BlendMode blendMode)
{
	/* TODO 2.3 Generate a new particle from the pool
		- Use firstAvailable to Init the particle.
		- But remember to move the firstAvailable pointer to the next particles so we don't lose track of it.
		- Also check first that the pool is not empty befor doing anything. Use assert for this.

	*/
}

bool ParticlePool::Update(float dt)
{
	bool ret = false;

	/* TODO 2.4 Update and draw living particles in the pool. 
		- If it's alive update it, draw it and make sure to return true
		- If a particle is dead it becomes the first available in the pool. 
		  Use IsAlive() method to check this.
	*/

	return ret;
}