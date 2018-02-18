#include "Particle.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Window.h"
#include "p2Log.h"
#include <math.h>


Particle::Particle():life(0), start_life(0) {}

void Particle::Init(iPoint pos, float speed, float angle, float start_radius, uint life)
{
	pState.pLive.pos = pos;
	pState.pLive.vel.x = speed * cos(DEG_TO_RAD(angle));
	pState.pLive.vel.y = -speed * sin(DEG_TO_RAD(angle));
	this->life = this->start_life = life;
	pState.pLive.radius = pState.pLive.start_radius = start_radius;
}

bool Particle::Animate(float dt)
{
	if (!IsAlive()) return false;

	life--;

	pState.pLive.ageRatio = (float)this->life / (float)this->start_life;
	pState.pLive.radius = pState.pLive.start_radius * pState.pLive.ageRatio;
	pState.pLive.alpha = (int)(pState.pLive.ageRatio * 255.0f);

	pState.pLive.pos.x += pState.pLive.vel.x * dt;
	pState.pLive.pos.y += pState.pLive.vel.y * dt;

	App->render->DrawCircle(pState.pLive.pos.x, pState.pLive.pos.y, ceil(pState.pLive.radius), 255, 0, 0, pState.pLive.alpha, true);

	return life == 0;
}

bool Particle::IsAlive()
{
	return (life > 0);
}

Particle * Particle::GetNext()
{
	return pState.next;
}

void Particle::SetNext(Particle * next)
{
	pState.next = next;
}
