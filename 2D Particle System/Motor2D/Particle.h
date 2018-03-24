#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "p2Point.h"
#include "Particle.h"
#include "SDL/include/SDL.h"

#define PI 3.14159265359f
#define DEG_TO_RAD(a) a * PI / 180.0f
#define RAD_TO_DEG(a) a * 180.0f / PI

struct SDL_Texture;

class Particle
{
	private:

	uint life = 0, start_life = 0;

	SDL_Rect pRect;

	union ParticleInfo
	{
		// This struct holds the state of the particle when 
		// it's being update (it's still alive).
		struct ParticleState
		{
			iPoint pos;
			iPoint vel;
			float radius, start_radius;
			float ageRatio;
			int alpha;
			float angle;

			ParticleState() {}

		} pLive;

		// If the particle is dead, then the 'next' member comes 
		// into play and the struct it's not used. This pointer
		// called 'next' holds a pointer to the next available 
		// particle after this one.
		Particle* next;

		ParticleInfo() {}
	} pState;

	public:

	Particle();
	void Init(iPoint pos, float speed, float angle, float start_radius, uint life);

	void Update(float dt);

	void Draw();

	bool IsAlive();

	Particle* GetNext();
	void SetNext(Particle* next);
};

#endif