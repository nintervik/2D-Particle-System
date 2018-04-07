#ifndef __J1_PARTICLE_SYSTEM_H__
#define __J1_PARTICLE_SYSTEM_H__

#include "p2Point.h"
#include "j1Module.h"
#include "Emitter.h"
#include <list>
#include <string>
#include "SDL/include/SDL.h"

#define MAX_NUM_EMITTERS_TYPE 6

class Emitter;
struct SDL_Texture;
struct SDL_Rect;
struct SDL_Color;
enum EmitterType;

class j1ParticleSystem : public j1Module
{

private:

	std::list<Emitter*> emittersList;
	SDL_Texture* particleAtlas = nullptr;
	std::string nameParticleAtlas;

	struct EmitterData
	{
		fPoint angleRange = { 0.0f, 0.0f };
		float maxSpeed = 0.0f;
		float startSize = 0.0f, endSize = 0.0f;
		uint emitNumber = 0u;
		uint emitVariance = 0u;
		uint maxParticleLife = 0u;
		SDL_Rect textureRect = { 0, 0 };
		double lifetime = -1.0f;
		EmitterType type;
		SDL_Color startColor = { 0, 0, 0, 0 };
		SDL_Color endColor = { 0, 0, 0, 0 };
		SDL_BlendMode blendMode = SDL_BlendMode::SDL_BLENDMODE_NONE;
	};

	EmitterData vecEmitterData[MAX_NUM_EMITTERS_TYPE];
	
public:

	j1ParticleSystem();

	// Destructor
	virtual ~j1ParticleSystem();

	// Called when before render is available
	bool Awake(pugi::xml_node& config);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Emitter methods
	Emitter* AddEmiter(fPoint pos, EmitterType type);
	bool RemoveEmitter(Emitter& emitter);
	bool RemoveAllEmitters();
	SDL_Texture* GetParticleAtlas() const;
	void LoadEmitterData(pugi::xml_node& config, EmitterType type);
};

#endif