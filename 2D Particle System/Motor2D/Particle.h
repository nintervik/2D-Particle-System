#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "p2Point.h"
#include "SDL/include/SDL.h"

struct SDL_Texture;

class Particle
{
	private:

	uint life = 0, startLife = 0;

	union ParticleInfo
	{
		// This struct holds the state of the particle when 
		// it's being update (it's still alive).
		struct ParticleState
		{
			fPoint pos;
			fPoint vel;
			float radius, start_radius;
			float ageRatio;
			float angle;
			SDL_Rect pRect;
			SDL_Rect rectSize;
			SDL_Color startColor;
			SDL_Color endColor;
			SDL_BlendMode blendMode;
			float t;

			ParticleState() {}

		} pLive;

		// If the particle is dead, then the 'next' member comes 
		// into play and the struct it's not used. This pointer
		// called 'next' holds a pointer to the next available 
		// particle after this one.
		Particle* next;

		ParticleInfo() {}
	} pState;

	struct Vortex
	{
		fPoint pos = { 350.0f, 400.0f };
		float speed = 25.0f;
		float scale = 30.0f;
	};

	Vortex vortex;

	public:

	Particle();
	void Init(fPoint pos, float speed, float angle, float start_radius, uint life, SDL_Rect textureRect, SDL_Color startColor, SDL_Color endColor, SDL_BlendMode blendMode);

	void Update(float dt);
	void Draw();

	bool IsAlive();

	Particle* GetNext();
	void SetNext(Particle* next);

	SDL_Color RgbInterpolation(SDL_Color startColor, SDL_Color endColor, float timeStep);
};

#endif