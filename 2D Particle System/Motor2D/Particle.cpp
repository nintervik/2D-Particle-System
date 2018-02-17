#include "Particle.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Window.h"


Particle::Particle(iPoint pos, iPoint vel, uint life)
{
	this->pos = pos;
	this ->endTime = SDL_GetTicks() + life;
	this->vel = vel;
}

void Particle::MoveParticle()
{
	pos.x += vel.x;
	pos.y += vel.y;

	uint w, h;
	App->win->GetWindowSize(w, h);

	if (pos.x < 0)
		pos.x = 0;
	if (pos.y < 0)
		pos.y = 0;

	if (pos.x > w)
		pos.x = w - 1;
	if (pos.y > h)
		pos.y = h - 1;
}

void Particle::Draw()
{
	App->render->DrawQuad({ pos.x, pos.y, 100, 100 }, 234, 44, 22, 100);
}

bool Particle::isDead()
{
	uint w, h;
	App->win->GetWindowSize(w, h);

	return (SDL_GetTicks() >= endTime || pos.x == 0 || pos.y == 0 ||
			pos.x == w - 1 || pos.y == h - 1);
}