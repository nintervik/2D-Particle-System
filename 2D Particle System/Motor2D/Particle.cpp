#include "Particle.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1ParticleSystem.h"
#include "p2Defs.h"


Particle::Particle():life(0), start_life(0) 
{

}

void Particle::Init(fPoint pos, float speed, float angle, float start_radius, uint life, SDL_Rect textureRect)
{
	pState.pLive.pos = pos;
	pState.pLive.vel.x = speed * cos(DEG_TO_RAD(angle));
	pState.pLive.vel.y = -speed * sin(DEG_TO_RAD(angle));
	this->life = this->start_life = life;
	pState.pLive.radius = pState.pLive.start_radius = start_radius;
	pState.pLive.pRect = pState.pLive.rectSize = textureRect;
}

void Particle::Update(float dt)
{
	life--;

	pState.pLive.ageRatio = (float)this->life / (float)this->start_life;
	pState.pLive.alpha = (int)(pState.pLive.ageRatio * 255.0f);
	pState.pLive.radius = pState.pLive.start_radius * pState.pLive.ageRatio;
	pState.pLive.rectSize.w = pState.pLive.rectSize.h = pState.pLive.radius;
	pState.pLive.alpha = (uint)(pState.pLive.ageRatio * 255.0f);

	pState.pLive.pos.x += pState.pLive.vel.x * dt;
	pState.pLive.pos.y += pState.pLive.vel.y * dt;
}

void Particle::Draw()
{
	SDL_Rect rectTest = { pState.pLive.start_radius , pState.pLive.start_radius };
	int centerX = pState.pLive.pos.x + ((rectTest.w - pState.pLive.rectSize.w) / 2);
	int centerY = pState.pLive.pos.y + ((rectTest.h - pState.pLive.rectSize.h) / 2);

	// SDL_Texture* texture, float alpha, int x, int y, const SDL_Rect* section, const SDL_Rect* rectSize, float speed, double angle, int pivot_x, int pivot_y
	App->render->BlitParticle(App->psystem->GetParticleAtlas(), pState.pLive.alpha, centerX, centerY, &pState.pLive.pRect, &pState.pLive.rectSize);
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