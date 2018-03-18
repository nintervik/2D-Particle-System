#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
//#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Scene.h"
#include <time.h>

j1Scene::j1Scene() : j1Module()
{
	name = "scene";
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	srand(time(NULL));

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	float randSpeed = rand() % (50 - 200 + 1) + 50;
	float randAngle = rand() % (-45 + 45 + 1) + 45;
	int randLife = 50;
	int randRadius = rand() % (5 - 25 + 1) + 5;

	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
	int mx, my;
	App->input->GetMousePosition(mx, my);
	iPoint pos(mx, my);

	testEmitter = App->psystem->AddEmiter(pos, randAngle, randSpeed);
	}

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		App->psystem->RemoveAllEmitters();
	}
	
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	std::list<Emitter*>::reverse_iterator it;

	testEmitter = nullptr;

	return true;
}


// TODO IMPORTANT:

// 1. Make a random method to generate a number from -1 to 1 (check bookmarks) and muliply it for a value
// 2. Random numbers should be handled inside the emitter classs, not in scene
// 3. Each emitter should have a rect that will be passed to particle as an argument in its constructor
// 4. Particle equations will be done in emitter, all particles are the same, the emitter is the one who changes. 
//    Emitters should be a parent class and types of emitters will be child classes maybe.
// 5. Modify Blit() method to take RGB and alpha as arguments. Look for belnding modes too (check Drive notes)
// 6. Emitter could have an enum to determine shape, or a shape pos in each child class
// 7. Particles should have acceleration and emitters should have motion equations to calculate physics
// 8. Emitter should have an emission rate according to framerate and particles' life
// 9. Remember that particle values should be floats no matter what. 
//    We don't want to lose precision when multiplying by dt. Then Blit() will ceil() them but that's okay
//    as calcculations will already be done.

// Emitter rate
// Emitter shape
// Emitter should be able to be active or not
// Pool should be a dynamic array (vector) and you should be able to
//   say with a parameter how big the pool is or the emission rate and then the pool size should 
//   change according to that. Use allocate and shrink_to_fit methods in vector.
// Read attributes from an xml. When setting an emitter you say "fire" and read from the xml the attributes
// Emitters should be able to spaen other emitters
// Emitters should be able to sapwn particle for a certain time and the stop for example.
//   Or even change its type and then start sapwning another types of particles. So it's like
//   a chain of emissions. Fire, explosion, smoke in a loop for example.
// Blending modes
// Alpha changing over time
// Color changing over time
// Random generator
// Particles acceleration movement
