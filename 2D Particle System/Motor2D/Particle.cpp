#include "Particle.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1ParticleSystem.h"


Particle::Particle():life(0), start_life(0) 
{
	// TODO: particle should recieve a texture to load. Maybe we could store particle texture
	// types inside a vector in the ParticleSystem. We could even do an enum type for each 
	// texture. Also, we could store each texture inside each emitter class.

	pRect.x = 0;
	pRect.y = 0;
	pRect.w = 32;
	pRect.h = 32;
}

void Particle::Init(iPoint pos, float speed, float angle, float start_radius, uint life)
{
	pState.pLive.pos = pos;
	pState.pLive.vel.x = speed * cos(DEG_TO_RAD(angle));
	pState.pLive.vel.y = -speed * sin(DEG_TO_RAD(angle));
	this->life = this->start_life = life;
	pState.pLive.radius = pState.pLive.start_radius = start_radius;
}

void Particle::Update(float dt)
{
	life--;

	pState.pLive.ageRatio = (float)this->life / (float)this->start_life;
	pState.pLive.alpha = (int)(pState.pLive.ageRatio * 255.0f);
	pState.pLive.radius = pState.pLive.start_radius * pState.pLive.ageRatio;
	pState.pLive.alpha = (uint)(pState.pLive.ageRatio * 255.0f);

	pState.pLive.pos.x += pState.pLive.vel.x * dt;
	pState.pLive.pos.y += pState.pLive.vel.y * dt;
}

void Particle::Draw()
{
	App->render->BlitParticle(App->psystem->GetParticleAtlas(), pState.pLive.alpha, pState.pLive.pos.x, pState.pLive.pos.y, &pRect);

	// Render circle
	// App->render->DrawCircle(pState.pLive.pos.x, pState.pLive.pos.y, ceil(pState.pLive.radius), 255, 0, 0, pState.pLive.alpha, true);
}

bool Particle::IsAlive()
{
	return (life > 0);
}

Particle* Particle::GetNext()
{
	return pState.next;
}

void Particle::SetNext(Particle* next)
{
	pState.next = next;
}