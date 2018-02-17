#include "Particle.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Window.h"
#include "p2Log.h"
#include <math.h>

Particle::Particle(iPoint pos, float speed, float angle, uint life)
{
	this->pos = pos;
	vel.x = speed * cos(DEG_TO_RAD(angle));
	vel.y = -speed * sin(DEG_TO_RAD(angle));
	this->life = life;
}

void Particle::Move(float dt)
{
	life -= dt;
	if (life > 0)
	{
		pos.x += vel.x * dt;
		pos.y += vel.y * dt;
	}

}

void Particle::Draw()
{
	App->render->DrawCircle(pos.x, pos.y, 15, 255, 0, 0, 100, true);
}

void Particle::Update(float dt)
{
	Move(dt);
	Draw();
}

bool Particle::IsDead()
{
	if (life > 0)
		return false;
	else
		return true;
}