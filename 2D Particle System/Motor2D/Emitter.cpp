#include "Emitter.h"
#include <time.h>
#include <stdlib.h>

// TODO: emitter should inherit from j1Module...

Emitter::Emitter(iPoint pos, float angle, float speed) : pos(pos), angle(angle), speed(speed) 
{ 
	srand(time(NULL));
}

void Emitter::Update(float dt)
{
	int randSpeed = rand() % (50 - 200 + 1) + 50;
	int randAngle = rand() % (0 - 360 + 1) + 0;
	int randRadius = rand() % (5 - 25 + 1) + 5;

	emitterPool.Generate(pos, randSpeed, randAngle, randRadius, 50);
	emitterPool.Update(dt);
}

void Emitter::Draw(SDL_Texture * texture)
{
	
}
