#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "Particle.h"
#include "ParticlePool.h"
#include "Emitter.h"
#include "p2Point.h"

struct SDL_Texture;

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

private:

	Emitter* eFire = nullptr;
	Emitter* eSmoke = nullptr;
	Emitter* eFlame = nullptr;
	Emitter* eWave_1 = nullptr;
	Emitter* eWave_2 = nullptr;
	Emitter* eBurst_1 = nullptr;
	Emitter* eBurst_2 = nullptr;
	Emitter* eBubbles = nullptr;
	Emitter* eSpark = nullptr;
	Emitter* ePixelSmoke = nullptr;
	SDL_Rect rect = { 0, 0, 400, 400 };
	SDL_Texture* torchTex = nullptr;

};

#endif // __j1SCENE_H__