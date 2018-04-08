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

	eFire = App->psystem->AddEmiter(pos, EmitterType::EMITTER_TYPE_FIRE);
	}

	if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN)
	{
		int mx, my;
		App->input->GetMousePosition(mx, my);
		fPoint pos((float)mx, (float)my);
		eSmoke = App->psystem->AddEmiter(pos, EmitterType::EMITTER_TYPE_SMOKE);
	}

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		int mx, my;
		App->input->GetMousePosition(mx, my);
		fPoint pos((float)mx, (float)my);
		eExplosion = App->psystem->AddEmiter(pos, EmitterType::EMITTER_TYPE_EXPLOSION);
		eBurst = App->psystem->AddEmiter(pos, EmitterType::EMITTER_TYPE_BURST);
	}

	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		int mx, my;
		App->input->GetMousePosition(mx, my);
		fPoint pos((float)mx, (float)my);
		eFlame = App->psystem->AddEmiter(pos, EmitterType::EMITTER_TYPE_FLAME);
	}

	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		int mx, my;
		App->input->GetMousePosition(mx, my);
		fPoint pos((float)mx, (float)my);
		eFlame = App->psystem->AddEmiter(pos, EmitterType::EMITTER_TYPE_FIRE_PURPLE);
	}

	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
	{
		int mx, my;
		App->input->GetMousePosition(mx, my);
		fPoint pos((float)mx, (float)my);
		eBubbles = App->psystem->AddEmiter(pos, EmitterType::EMITTER_TYPE_BUBBLE);
	}

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		App->psystem->RemoveAllEmitters();
	}

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN && eFire != nullptr)
	{
		eFire->StopEmission(5000.0f);
	}

	if (eBubbles != nullptr )
	{
		int mx, my;
		App->input->GetMousePosition(mx, my);
		fPoint pos((float)mx, (float)my);
		eBubbles->MoveEmitter(pos);
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN && eFire != nullptr)
	{
		eFire->StartEmission(5000.0f);
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT && eSmoke != nullptr)
	{
		fPoint newPos = eSmoke->GetEmitterPos();
		newPos.x += 5.0f;
		
		eSmoke->MoveEmitter(newPos);
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT && eSmoke != nullptr)
	{
		fPoint newPos = eSmoke->GetEmitterPos();
		newPos.x -= 5.0f;

		eSmoke->MoveEmitter(newPos);
	}
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT && eSmoke != nullptr)
	{
		fPoint newPos = eSmoke->GetEmitterPos();
		newPos.y -= 5.0f;

		eSmoke->MoveEmitter(newPos);
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && eSmoke != nullptr)
	{
		fPoint newPos = eSmoke->GetEmitterPos();
		newPos.y += 5.0f;

		eSmoke->MoveEmitter(newPos);
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

	eSmoke = nullptr;
	eFire = nullptr;

	return true;
}

/* Things left TODO:

   -  Particle physics: vortex, linear or parabole.

   -  Emitters shapes.

   -  Add rotation as a parameter

   -  Control randomization parameters

   -  Animations instead of textures?

   -  Once everything is set up try to do different types of particles and create a 
      unique atlas to store all the textures needed for each type of particle.

   -  Look framerate calculations in app.

   -  Clean code, add comments and test!

   // TO IMPROVE
   
   - Emitters of emitters
    -  Emitters should be able to have a chain reaction, i.e: change its type and 
      then start spawning another types of particles. So it's like a chain of 
	  emissions. Fire, explosion, smoke in a loop for example.

	  ----

	  -  Emission rate could be lower than 1.

 */