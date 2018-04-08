
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
		if (emitterType == "fire_purple")
			LoadEmitterData(emitters, EmitterType::EMITTER_TYPE_FIRE_PURPLE);
		if (emitterType == "flame")
			LoadEmitterData(emitters, EmitterType::EMITTER_TYPE_FLAME);
		else if (emitterType == "smoke")
			LoadEmitterData(emitters, EmitterType::EMITTER_TYPE_SMOKE);
		else if (emitterType == "burst")
			LoadEmitterData(emitters, EmitterType::EMITTER_TYPE_BURST);
		else if (emitterType == "explosion")
			LoadEmitterData(emitters, EmitterType::EMITTER_TYPE_EXPLOSION);
		else if (emitterType == "bubbles")
			LoadEmitterData(emitters, EmitterType::EMITTER_TYPE_BUBBLE);
	
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

	return true;
}

Emitter* j1ParticleSystem::AddEmiter(fPoint pos, EmitterType type)
{
	Emitter* tmp_emitter = new Emitter(pos, vecEmitterData[type].emitNumber, vecEmitterData[type].emitVariance, vecEmitterData[type].maxParticleLife, vecEmitterData[type].angleRange, vecEmitterData[type].rotSpeed, vecEmitterData[type].maxSpeed, vecEmitterData[type].startSize, vecEmitterData[type].endSize,  vecEmitterData[type].textureRect, vecEmitterData[type].startColor, vecEmitterData[type].endColor, vecEmitterData[type].blendMode, vecEmitterData[type].lifetime);
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

	return ret;
}
 
SDL_Texture* j1ParticleSystem::GetParticleAtlas() const
{
	return particleAtlas;
}

void j1ParticleSystem::LoadEmitterData(pugi::xml_node & emitter, EmitterType type)
{
	EmitterData tmp;

	// Angle range
	tmp.angleRange.x = emitter.child("angleRange").attribute("min").as_float();
	tmp.angleRange.y = emitter.child("angleRange").attribute("max").as_float();

	tmp.rotSpeed = emitter.child("rotSpeed").attribute("value").as_double();

	tmp.maxSpeed = emitter.child("maxSpeed").attribute("value").as_float();
	tmp.startSize = emitter.child("size").attribute("startSize").as_float();
	tmp.endSize = emitter.child("size").attribute("endSize").as_float();
	tmp.emitNumber = emitter.child("emitNumber").attribute("value").as_uint();
	tmp.emitVariance = emitter.child("emitVariance").attribute("value").as_uint();
	tmp.maxParticleLife = emitter.child("maxParticleLife").attribute("value").as_uint();
	
	// Rect from particle atlas
	tmp.textureRect.x = emitter.child("textureRect").attribute("x").as_int();
	tmp.textureRect.y = emitter.child("textureRect").attribute("y").as_int();
	tmp.textureRect.w = emitter.child("textureRect").attribute("w").as_int();
	tmp.textureRect.h = emitter.child("textureRect").attribute("h").as_int();
	
	// Lifetime of emitter
	tmp.lifetime = emitter.child("lifetime").attribute("value").as_double();

	// Start color
	tmp.startColor.r = emitter.child("startColor").attribute("r").as_uint();
	tmp.startColor.g = emitter.child("startColor").attribute("g").as_uint();
	tmp.startColor.b = emitter.child("startColor").attribute("b").as_uint();
	tmp.startColor.a = emitter.child("startColor").attribute("a").as_uint();

	// End color
	tmp.endColor.r = emitter.child("endColor").attribute("r").as_uint();
	tmp.endColor.g = emitter.child("endColor").attribute("g").as_uint();
	tmp.endColor.b = emitter.child("endColor").attribute("b").as_uint();
	tmp.endColor.a = emitter.child("endColor").attribute("a").as_uint();

	// Blend mode
	std::string blendModeString = emitter.child("blendMode").attribute("mode").as_string();

	if (blendModeString == "add")
		tmp.blendMode = SDL_BlendMode::SDL_BLENDMODE_ADD;
	else if (blendModeString == "blend")
		tmp.blendMode = SDL_BlendMode::SDL_BLENDMODE_BLEND;
	else if (blendModeString == "mod")
		tmp.blendMode = SDL_BlendMode::SDL_BLENDMODE_MOD;
	else if (blendModeString == "none")
		tmp.blendMode = SDL_BlendMode::SDL_BLENDMODE_NONE;

	vecEmitterData[type] = tmp;
}