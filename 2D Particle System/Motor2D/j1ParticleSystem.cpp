
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
		std::string emitterType = emitters.attribute("type").as_string();
		EmitterData tmpData;

		if (emitterType == "fire")
			LoadEmitterData(emitters, EmitterType::EMITTER_TYPE_FIRE);
		else if (emitterType == "fire2")
			LoadEmitterData(emitters, EmitterType::EMITTER_TYPE_FIRE2);
	
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

Emitter* j1ParticleSystem::AddEmiter(fPoint pos, EmitterType type)
{
	// uint emitNumber, uint emitVariance, uint maxParticleLife, fPoint angleRange, float maxSpeed, float maxSize, SDL_Rect textureRect, double lifeTime

	Emitter* tmp_emitter = new Emitter(pos, vecEmitterData[type].emitNumber, vecEmitterData[type].emitVariance, vecEmitterData[type].maxParticleLife, vecEmitterData[type].angleRange, vecEmitterData[type].maxSpeed, vecEmitterData[type].maxSize, vecEmitterData[type].textureRect, vecEmitterData[type].lifetime);
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

void j1ParticleSystem::LoadEmitterData(pugi::xml_node & emitter, EmitterType type)
{
	EmitterData tmp;

	tmp.angleRange.x = emitter.child("angleRange").attribute("min").as_float();
	tmp.angleRange.y = emitter.child("angleRange").attribute("max").as_float();
	tmp.maxSpeed = emitter.child("maxSpeed").attribute("value").as_float();
	tmp.maxSize = emitter.child("maxSize").attribute("value").as_float();
	tmp.emitNumber = emitter.child("emitNumber").attribute("value").as_uint();
	tmp.emitVariance = emitter.child("emitVariance").attribute("value").as_uint();
	tmp.maxParticleLife = emitter.child("maxParticleLife").attribute("value").as_uint();
	tmp.textureRect.x = emitter.child("textureRect").attribute("x").as_int();
	tmp.textureRect.y = emitter.child("textureRect").attribute("y").as_int();
	tmp.textureRect.w = emitter.child("textureRect").attribute("w").as_int();
	tmp.textureRect.h = emitter.child("textureRect").attribute("h").as_int();
	tmp.lifetime = emitter.child("lifetime").attribute("value").as_double();

	vecEmitterData[type] = tmp;
}