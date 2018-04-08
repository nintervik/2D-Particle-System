#include "Particle.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1ParticleSystem.h"
#include "p2Defs.h"


Particle::Particle():life(0) { }

void Particle::Init(fPoint pos, float speed, float angle, double rotSpeed, float startSize, float endSize, uint life, SDL_Rect textureRect, SDL_Color startColor, SDL_Color endColor, SDL_BlendMode blendMode)
{
	pState.pLive.pos = pos;
	pState.pLive.vel.x = speed * cos(DEG_TO_RAD(angle));
	pState.pLive.vel.y = -speed * sin(DEG_TO_RAD(angle));
	this->life = pState.pLive.startLife = life;
	pState.pLive.currentSize = pState.pLive.startSize = startSize;
	pState.pLive.endSize = endSize;
	pState.pLive.pRect = pState.pLive.rectSize = textureRect;
	pState.pLive.startColor = startColor;
	pState.pLive.endColor = endColor;
	pState.pLive.blendMode = blendMode;
	pState.pLive.startRotSpeed = rotSpeed;
	pState.pLive.currentRotSpeed = rotSpeed;
	pState.pLive.t = 0.0f;

	AddVortex({ 250.0f, 200.0f }, 25.0f, 30.0f);

}

void Particle::Update(float dt)
{
	life--;

	pState.pLive.ageRatio = (float)this->life / (float)pState.pLive.startLife;

	if (pState.pLive.startSize > pState.pLive.endSize && pState.pLive.currentSize <= pState.pLive.endSize)
		pState.pLive.currentSize = pState.pLive.startSize * pState.pLive.ageRatio;
	else if (pState.pLive.startSize < pState.pLive.endSize && pState.pLive.currentSize <= pState.pLive.endSize)
		pState.pLive.currentSize += 0.5f * (pState.pLive.endSize / pState.pLive.ageRatio - pState.pLive.endSize);

	pState.pLive.rectSize.w = pState.pLive.rectSize.h = pState.pLive.currentSize;

	CalculatePosFromVortex(dt);
}

void Particle::Draw()
{
	SDL_Rect rectTest = { (int)pState.pLive.startSize, (int)pState.pLive.startSize };
	float centerX = pState.pLive.pos.x + ((rectTest.w - pState.pLive.rectSize.w) / 2.0f);
	float centerY = pState.pLive.pos.y + ((rectTest.h - pState.pLive.rectSize.h) / 2.0f); 

	SDL_Color resColor = pState.pLive.startColor;

	if (pState.pLive.startLife > 15)
		resColor = RgbInterpolation(pState.pLive.startColor, pState.pLive.endColor, pState.pLive.t);

	if (pState.pLive.currentRotSpeed > 1)
		int a = 0;

	App->render->BlitParticle(App->psystem->GetParticleAtlas(), (int)centerX, (int)centerY, &pState.pLive.pRect, &pState.pLive.rectSize, resColor, pState.pLive.blendMode, 1.0f, pState.pLive.currentRotSpeed);
	pState.pLive.currentRotSpeed += pState.pLive.startRotSpeed;

	pState.pLive.t += (1.0f / (float)pState.pLive.startLife);

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
	finalColor.a = startColor.a + (endColor.a - startColor.a) * timeStep;

	return finalColor;
}

void Particle::AddVortex(fPoint pos, float speed, float scale)
{
	vortex.pos = pos;
	vortex.speed = speed;
	vortex.scale = scale;
}

void Particle::CalculatePosFromVortex(float dt)
{
	float dx = pState.pLive.pos.x - vortex.pos.x;
	float dy = pState.pLive.pos.y - vortex.pos.y;
	float vx = -dy * vortex.speed;
	float vy = dx * vortex.speed;
	float factor = 1.0f / (1.0f + (dx * dx + dy * dy) / vortex.scale);

	pState.pLive.pos.x += (vx - pState.pLive.vel.x) * factor + pState.pLive.vel.x * dt;
	pState.pLive.pos.y += (vy - pState.pLive.vel.y) * factor + pState.pLive.vel.y * dt;
}