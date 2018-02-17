#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "p2Point.h"
#include "p2Defs.h"

#define PI 3.14159265359f

class Particle
{
	private:
	
	iPoint pos = { 0, 0 };
	iPoint vel = { 0, 0 };
	uint32 endTime;
	bool dead = false;
	float radAngle = 0.0f;


	public:

	Particle::Particle(iPoint pos, iPoint vel, uint life);

	void MoveParticle();
	void Draw();
	bool isDead();
};

#endif