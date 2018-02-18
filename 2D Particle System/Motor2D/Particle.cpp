#include "Particle.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Window.h"
#include "p2Log.h"
#include <math.h>


Particle::Particle():life(0), start_life(0) {}

void Particle::Init(iPoint pos, float speed, float angle, float start_radius, uint life)
{
	this->pos = pos;
	vel.x = speed * cos(DEG_TO_RAD(angle));
	vel.y = -speed * sin(DEG_TO_RAD(angle));
	this->life = this->start_life = life;
	this->radius = this->start_radius = start_radius;
}

void Particle::Move(float dt)
{
	life -= dt;

	if (!IsDead())
	{
		ageRatio = (float)this->life / (float)this->start_life;
		radius = start_radius * ageRatio;
		alpha = (int)(ageRatio * 255.0f);

		pos.x += vel.x * dt;
		pos.y += vel.y * dt;
	}

}

void Particle::Draw()
{
	App->render->DrawCircle(pos.x, pos.y, floor(radius), 255, 0, 0, alpha, true);
}

void Particle::Update(float dt)
{
	Move(dt);
	Draw();
}

bool Particle::IsDead()
{
	return (life <= 0);
}