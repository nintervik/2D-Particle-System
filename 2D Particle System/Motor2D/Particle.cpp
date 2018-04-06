#include "Particle.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1ParticleSystem.h"
#include "p2Defs.h"


Particle::Particle():life(0), startLife(0) { }

void Particle::Init(fPoint pos, float speed, float angle, float start_radius, uint life, SDL_Rect textureRect, SDL_Color startColor, SDL_Color endColor, SDL_BlendMode blendMode)
{
	pState.pLive.pos = pos;
	pState.pLive.vel.x = speed * cos(DEG_TO_RAD(angle));
	pState.pLive.vel.y = -speed * sin(DEG_TO_RAD(angle));
	this->life = this->startLife = life;
	pState.pLive.radius = pState.pLive.start_radius = start_radius;
	pState.pLive.pRect = pState.pLive.rectSize = textureRect;
	pState.pLive.startColor = startColor;
	pState.pLive.endColor = endColor;
	pState.pLive.blendMode = blendMode;
	pState.pLive.t = 0.0f;
}

void Particle::Update(float dt)
{
	life--;

	pState.pLive.ageRatio = (float)this->life / (float)this->startLife;
	pState.pLive.startColor.a = (pState.pLive.ageRatio * 255.0f);

	if (pState.pLive.radius < 100.0f)
		pState.pLive.radius = pState.pLive.start_radius / pState.pLive.ageRatio;



	pState.pLive.rectSize.w = pState.pLive.rectSize.h = pState.pLive.radius;

	float dx = pState.pLive.pos.x - vortex.pos.x;
	float dy = pState.pLive.pos.y - vortex.pos.y;
	float vx = -dy * vortex.speed;
	float vy = dx * vortex.speed;
	float factor = 1.0f / (1.0f + (dx * dx + dy * dy) / vortex.scale);

	pState.pLive.pos.x += (vx - pState.pLive.vel.x) * factor + pState.pLive.vel.x * dt;
	pState.pLive.pos.y += (vy - pState.pLive.vel.y) * factor + pState.pLive.vel.y * dt;

	//pState.pLive.pos.x += pState.pLive.vel.x * dt;
	//pState.pLive.pos.y += pState.pLive.vel.y * dt;
}

void Particle::Draw()
{
	SDL_Rect rectTest = { (int)pState.pLive.start_radius, (int)pState.pLive.start_radius };
	float centerX = pState.pLive.pos.x + ((rectTest.w - pState.pLive.rectSize.w) / 2);
	float centerY = pState.pLive.pos.y + ((rectTest.h - pState.pLive.rectSize.h) / 2); 

	SDL_Color resColor = pState.pLive.startColor;

	if (startLife > 15)
	{
		resColor = RgbInterpolation(pState.pLive.startColor, pState.pLive.endColor, pState.pLive.t);
	}
	 
	resColor.a = pState.pLive.startColor.a;


	
	App->render->BlitParticle(App->psystem->GetParticleAtlas(), (int)centerX, (int)centerY, &pState.pLive.pRect, &pState.pLive.rectSize, resColor, pState.pLive.blendMode);
	
	pState.pLive.t += (1.0f / (float)startLife);

	if (pState.pLive.t >= 1.0f)
		pState.pLive.t = 0.0f;
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

SDL_Color Particle::RgbInterpolation(SDL_Color startColor, SDL_Color endColor, float timeStep)
{
	SDL_Color finalColor;

	finalColor.r = startColor.r + (endColor.r - startColor.r) * timeStep;
	finalColor.g = startColor.g + (endColor.g - startColor.g) * timeStep;
	finalColor.b = startColor.b + (endColor.b - startColor.b) * timeStep;

	return finalColor;
}