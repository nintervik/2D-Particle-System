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
	fPoint pos((float)mx, (float)my);

	testEmitter1 = App->psystem->AddEmiter(pos, EmitterType::EMITTER_TYPE_FIRE);
	}

	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		int mx, my;
		App->input->GetMousePosition(mx, my);
		fPoint pos((float)mx, (float)my);
		testEmitter2 = App->psystem->AddEmiter(pos, EmitterType::EMITTER_TYPE_FIRE2);
	}

	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		int mx, my;
		App->input->GetMousePosition(mx, my);
		fPoint pos((float)mx, (float)my);
		testEmitter3 = App->psystem->AddEmiter(pos, EmitterType::EMITTER_TYPE_FIRE3);
	}

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		App->psystem->RemoveEmitter(*testEmitter1);
	}

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN && testEmitter1 != nullptr)
	{
		testEmitter1->StopEmission(5000.0f);
	}

	if (testEmitter1 != nullptr)
	{
		int mx, my;
		App->input->GetMousePosition(mx, my);
		fPoint pos((float)mx, (float)my);
		testEmitter1->MoveEmitter(pos);
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN && testEmitter1 != nullptr)
	{
		testEmitter1->StartEmission(5000.0f);
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT && testEmitter1 != nullptr)
	{
		fPoint newPos = testEmitter1->GetEmitterPos();
		newPos.x += 5.0f;
		
		testEmitter1->MoveEmitter(newPos);
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT && testEmitter1 != nullptr)
	{
		fPoint newPos = testEmitter1->GetEmitterPos();
		newPos.x -= 5.0f;

		testEmitter1->MoveEmitter(newPos);
	}
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT && testEmitter1 != nullptr)
	{
		fPoint newPos = testEmitter1->GetEmitterPos();
		newPos.y -= 5.0f;

		testEmitter1->MoveEmitter(newPos);
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && testEmitter1 != nullptr)
	{
		fPoint newPos = testEmitter1->GetEmitterPos();
		newPos.y += 5.0f;

		testEmitter1->MoveEmitter(newPos);
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

	testEmitter1 = nullptr;

	return true;
}

/* Things left TODO:

   -  Particle physics: movement equations + bezier + vortex turbulence.

   -  Look framerate calculations in app.

   -  Method to apply forces.
   
   -  Acceletation should be a parameter?

   -  Emitters shapes.

   -  Emitters should be able to spawn other emitters.

   -  Emitters should be able to have a chain reaction, i.e: change its type and 
      then start spawning another types of particles. So it's like a chain of 
	  emissions. Fire, explosion, smoke in a loop for example.

   -  Once everything is set up try to do different types of particles and create a 
      unique atlas to store all the textures needed for each type of particle.

   -  Emission rate could be lower than 1.

   -  Clean code, add comments and test!

 */