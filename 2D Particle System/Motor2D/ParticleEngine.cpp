#include "ParticleEngine.h"

ParticleEngine::ParticleEngine(int maxParticles, iPoint pos)
{
	this->pos.x = pos.x;
	this->pos.y = pos.y;
	this->maxParticles = maxParticles;

	for (int i = 0; i < maxParticles; i++)
	{
		iPoint position(pos.x + rand() % 6 - 3, pos.y + rand() % 6 - 3);
		iPoint velocity(pos.x + rand() % 10 - 5, pos.y + rand() % 10 - 5);

		particles.push_back(new Particle(position, velocity, 500 + rand() % 1000));
	}
}

ParticleEngine::~ParticleEngine()
{
	for (int i = 0; i < maxParticles; i++)
	{
		delete particles[i];
		particles[i] = nullptr;
	}
}

void ParticleEngine::Refresh()
{
	for (int i = 0; i < maxParticles; i++)
	{
		if (particles[i]->isDead())
		{
			delete particles[i];
			particles[i] = nullptr;

			iPoint position(pos.x + rand() % 6 - 3, pos.y + rand() % 6 - 3);
			iPoint velocity(pos.x + rand() % 10 - 5, pos.y + rand() % 10 - 5);

			particles[i] = new Particle(position, velocity, 500 + rand() % 1000);
		}
		else
		{
			particles[i]->MoveParticle();
			particles[i]->Draw();
		}
	}
}