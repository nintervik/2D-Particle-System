
#include "p2Log.h"
#include "j1ParticleSystem.h"
#include "j1App.h"

// TODO: we should be able to add different types of emitters.
// For now, we wil stay with one to make sure it works. Then we
// can add more.

j1ParticleSystem::j1ParticleSystem() : j1Module()
{
	name = "psystem";
}

j1ParticleSystem::~j1ParticleSystem()
{
	
}

bool j1ParticleSystem::Awake(pugi::xml_node &)
{
	return true;
}

bool j1ParticleSystem::Start()
{
	return true;
}

// TODO: need to figure out if only call update or also preupdate.
// This will depend on the way the emitter is organized in terms of
// drawing and updating the particles with one or more methods.
bool j1ParticleSystem::PreUpdate()
{
	/*for (int i = 0; i < emitters.size(); i++)
		if (emitters.at(i) != nullptr) emitters[i]->Update();*/

	return true;
}

bool j1ParticleSystem::Update(float dt)
{
	return false;
}

bool j1ParticleSystem::PostUpdate()
{
	for (uint i = emitters.size() - 1; i >= 0; i--) 
	{
		if (emitters[i]->to_destroy) 
		{
			delete(emitters[i]);
			emitters[i] = nullptr;

			if (!emitters.empty())
				emitters.pop_back();
			else
			{
				LOG("Error removing emitter.");
				return false;
			}
		}
	}
}

bool j1ParticleSystem::CleanUp()
{
	LOG("Freeing emitters from the system.");

	for (int i = 0; i < emitters.size(); i++)
	{
		if (emitters[i] != nullptr)
		{
			delete emitters[i];
			emitters[i] = nullptr;

			if (!emitters.empty())
				emitters.pop_back();
			else
			{
				LOG("Error removing emitter.");
				return false;
			}
		}
	}

	emitters.clear();

	return false;
}

Emitter * j1ParticleSystem::AddEmiter(/*arguments for the constructor*/)
{
	Emitter* tmp_emitter = nullptr;/*new Emitter(arguments for the constructor);*/
	emitters.push_back(tmp_emitter);
	
	return tmp_emitter;
}

bool j1ParticleSystem::RemoveEmitter(Emitter & emitter)
{
	for (uint i = 0; i < emitters.size(); i++) 
	{
		if (emitters.at(i) == &emitter) 
		{
			emitters[i]->to_destroy = true;
			return true;
		}
	}

	return false;
}

bool j1ParticleSystem::RemoveAllEmitters()
{
	bool ret = false;

	for (uint i = 0; i < emitters.size(); i++) 
	{
		if (emitters.at(i) != nullptr) emitters[i]->to_destroy = true;
		ret = true;
	}

	return ret;
}