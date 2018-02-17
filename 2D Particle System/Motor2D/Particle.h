#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "p2Point.h"
#include "p2Defs.h"

#define PI 3.14159265359f
#define DEG_TO_RAD(a) a * PI / 180.0f
#define RAD_TO_DEG(a) a * 180.0f / PI

class Particle
{
	private:

	iPoint pos = { 0, 0 };
	iPoint vel = { 0, 0 };
	uint life = 0;
	bool dead = false;
	float angle = 0.0f;

	public:

	Particle::Particle(iPoint pos, float speed, float angle, uint life);

	void Move(float dt);
	void Draw();
	void Update(float dt);

	bool IsDead();

};

#endif