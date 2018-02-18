#include "ParticlePool.h"

void ParticlePool::Generate(iPoint pos, float speed, float angle, float start_radius, uint life)
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		{
			particles[i].Init(pos, speed, angle, start_radius, life);
			return;
		}
	}
}

void ParticlePool::Update(float dt)
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		particles[i].Update(dt);
	}
}
