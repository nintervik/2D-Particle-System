
#include "p2Log.h"
#include "j1ParticleSystem.h"
#include "j1App.h"
#include "j1Textures.h"



j1ParticleSystem::j1ParticleSystem() : j1Module()
{
	name = "psystem";

	LOG("Loading Languages");
	
}

j1ParticleSystem::~j1ParticleSystem()
{
	
}

bool j1ParticleSystem::Awake(pugi::xml_node& config)
{
	bool ret = true;

	pugi::xml_document	psystem_config;
	pugi::xml_node* node = &App->LoadEmitters(psystem_config);
	nameParticleAtlas = node->child("particleAtlas").attribute("name").as_string();
	
	for (pugi::xml_node emitters = node->child("particleAtlas").child("emitter"); emitters && ret; emitters = emitters.next_sibling("emitter"))
	{
		std::string tmp = emitters.attribute("type").as_string();

		if (tmp == "fire")
			int a = 0;
			//LoadAnimation(animations, &right_idle);
	

	}
	return ret;

}

bool j1ParticleSystem::Start()
{
	particleAtlas = App->tex->Load(nameParticleAtlas.c_str());

	return true;
}

bool j1ParticleSystem::PreUpdate()
{
	return true;
}

bool j1ParticleSystem::Update(float dt)
{
	// old code
	/*
	for (int i = 0; i < emitters.size(); i++)
	{
		if (emitters.at(i) != nullptr)
			emitters[i]->Update(dt);
	}
	*/

	std::list<Emitter*>::const_iterator it;

	for (it = emittersList.begin(); it != emittersList.end(); ++it)
	{
		if ((*it) != nullptr)
			(*it)->Update(dt);
	}

	return true;
}

bool j1ParticleSystem::PostUpdate()
{

	std::list<Emitter*>::const_iterator it;

	for (it = emittersList.begin(); it != emittersList.end(); ++it)
	{
		if ((*it)->toDestroy)
		{
			delete (*it);
			emittersList.erase(it);
		}
	}

	//old code
	/*
	for (int i = emitters.size() - 1; i >= 0 && !emitters.empty(); --i)
	{
		if (emitters[i]->to_destroy)
		{
			delete(emitters[i]);
			emitters[i] = nullptr;

			emitters.erase(emitters.cbegin() + i);
		}
	}

	emitters.shrink_to_fit();
	*/

	return true;
}

bool j1ParticleSystem::CleanUp()
{
	LOG("Freeing emitters from the system.");

	std::list<Emitter*>::const_iterator it;

	for (it = emittersList.begin(); it != emittersList.end(); ++it)
	{
		if ((*it) != nullptr)
			delete (*it);
	}

	emittersList.clear();
	App->tex->UnLoad(particleAtlas);

	/*std::vector<Emitter*>::const_iterator itEmitter = this->emitters.begin();

	while (itEmitter!= this->emitters.end())
	{
		delete *itEmitter;
		itEmitter++;
	}

	emitters.clear();*/

	/*for (int i = 0; i < emitters.size(); i++)
	{
		if (emitters[i] != nullptr)
		{
			delete emitters[i];
			emitters[i] = nullptr;

			emitters.erase(emitters.cbegin() + i);
		}
	}*/


	
	return true;
}

// TODO: we should be able to add different types of emitters.
// For now, we wil stay with one to make sure it works. Then we
// can add more.

Emitter * j1ParticleSystem::AddEmiter(fPoint pos, uint emitNumber, uint emitVariance, uint maxParticleLife, fPoint angleRange, float maxSpeed, float maxSize, SDL_Rect textureRect, double lifeTime)
{
	Emitter* tmp_emitter = new Emitter(pos, emitNumber, emitVariance, maxParticleLife, angleRange, maxSpeed, maxSize, textureRect, lifeTime);
	emittersList.push_back(tmp_emitter);
	
	return tmp_emitter;
}

bool j1ParticleSystem::RemoveEmitter(Emitter & emitter)
{
	std::list<Emitter*>::const_iterator it;

	for (it = emittersList.begin(); it != emittersList.end(); ++it)
	{

		if ((*it) == &emitter)
		{
			(*it)->toDestroy = true;
			return true;
		}
	}

	/*
	for (uint i = 0; i < emitters.size(); i++) 
	{
		if (emitters.at(i) == &emitter) 
		{
			emitters[i]->to_destroy = true;
			return true;
		}
	}*/

	return false;
}

bool j1ParticleSystem::RemoveAllEmitters()
{
	bool ret = false;

	std::list<Emitter*>::const_iterator it;

	for (it = emittersList.begin(); it != emittersList.end(); ++it)
	{
		if ((*it) != nullptr) (*it)->toDestroy = true;
		ret = true;
	}

	/*for (uint i = 0; i < emitters.size(); i++) 
	{
		if (emitters.at(i) != nullptr) emitters[i]->to_destroy = true;
		ret = true;
	}*/

	return ret;
}
 
SDL_Texture* j1ParticleSystem::GetParticleAtlas() const
{
	return particleAtlas;
}