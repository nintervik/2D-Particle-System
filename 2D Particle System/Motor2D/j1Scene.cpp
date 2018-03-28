#include "j1App.h"
#include "j1Input.h"
#include "j1Scene.h"
#include "p2Log.h"

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

	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
	int mx, my;
	App->input->GetMousePosition(mx, my);
	iPoint pos(mx, my);

	testEmitter = App->psystem->AddEmiter(pos, 1, 5, 100, { 0.0f, 120.0f }, 200.0f, 100.0f, { 0, 0, 128, 128 });
	}

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		App->psystem->RemoveAllEmitters();
	}

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN && testEmitter != nullptr)
	{
		testEmitter->StopEmission(5000.0f);
	}

	if (testEmitter != nullptr)
	{
		int mx, my;
		App->input->GetMousePosition(mx, my);
		iPoint pos(mx, my);
		testEmitter->MoveEmitter(pos);
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN && testEmitter != nullptr)
	{
		testEmitter->StartEmission();
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT && testEmitter != nullptr)
	{
		iPoint newPos = testEmitter->GetEmitterPos();
		newPos.x += 5;
		
		testEmitter->MoveEmitter(newPos);
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT && testEmitter != nullptr)
	{
		iPoint newPos = testEmitter->GetEmitterPos();
		newPos.x -= 5;

		testEmitter->MoveEmitter(newPos);
	}
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT && testEmitter != nullptr)
	{
		iPoint newPos = testEmitter->GetEmitterPos();
		newPos.y -= 5;

		testEmitter->MoveEmitter(newPos);
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && testEmitter != nullptr)
	{
		iPoint newPos = testEmitter->GetEmitterPos();
		newPos.y += 5;

		testEmitter->MoveEmitter(newPos);
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

	testEmitter = nullptr;

	return true;
}


// TODO IMPORTANT:

// 1. Make a random method to generate a number from -1 to 1 (check bookmarks) and muliply it for a value - done
// 2. Random numbers should be handled inside the emitter classs, not in scene - done
// 3. Each emitter should have a rect that will be passed to particle as an argument in its constructor
// 4. Particle equations will be done in emitter, all particles are the same, the emitter is the one who changes. 
//    Emitters should be a parent class and types of emitters will be child classes maybe.
// 5. Modify Blit() method to take RGB and alpha as arguments. Look for belnding modes too (check Drive notes) - in progress
// 6. Emitter could have an enum to determine shape, or a shape pos in each child class
// 7. Particles should have acceleration and emitters should have motion equations to calculate physics
// 8. Emitter should have an emission rate according to framerate and particles' life - done
// 9. Remember that particle values should be floats no matter what. 
//    We don't want to lose precision when multiplying by dt. Then Blit() will ceil() them but that's okay
//    as calculations will already be done.

// Emitter rate -done
// Emitter shape
// Rect for textures in emitters
// Emitter should be able to be active or not
// Pool should be a dynamic array (vector) and you should be able to
//   say with a parameter how big the pool is or the emission rate and then the pool size should 
//   change according to that. Use allocate and shrink_to_fit methods in vector. -
//   Formula: emitter rate pdf  and pool size = (max particles per frame) * (max life of a particle)
// Read attributes from an xml. When setting an emitter you say "fire" and read from the xml the attributes
// Emitters should be able to spawn other emitters
// Emitters should be able to spawn particle for a certain time and the stop for example.
//   Or even change its type and then start spawning another types of particles. So it's like
//   a chain of emissions. Fire, explosion, smoke in a loop for example. Do Start() and Stop() methods
// Move() method for emitters! IMPORTANT
// Blending modes
// Alpha changing over time -done
// Color changing over time
// Random generator - done
// Particles acceleration movement
