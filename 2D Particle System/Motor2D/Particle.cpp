#include "Particle.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1ParticleSystem.h"
#include "p2Defs.h"


Particle::Particle():life(0), start_life(0) 
{
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