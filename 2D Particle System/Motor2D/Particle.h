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

	SDL_Texture* pTexture = nullptr;
	SDL_Rect pRect;

	union ParticleInfo
	{
		// This struct holds the state of the particle when 
		// it's being update (it's still alive).
		struct ParticleState
		{
			iPoint pos = { 0, 0 };
			iPoint vel = { 0, 0 };
			float radius = 0.0f, start_radius = 0.0f;
			float ageRatio = 0.0f;
			int alpha = 0;
			float angle = 0.0f;

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

	bool Animate(float dt);

	bool IsAlive();

	Particle* GetNext();
	void SetNext(Particle* next);
};

#endif