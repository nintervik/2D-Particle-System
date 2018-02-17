#ifndef __PARTICLE_ENGINE_H__
#define __PARTICLE_ENGINE_H__

#include <vector>
#include "Particle.h"
#include <cstdlib>
#include <ctime>

class ParticleEngine
{
private:
	std::vector<Particle*> particles;
	iPoint pos;
	int maxParticles;

public:
	ParticleEngine(int maxParticles, iPoint pos);
	~ParticleEngine();

	void Refresh();
	




public:

};

#endif