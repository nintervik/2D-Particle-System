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
	fPoint pos(mx, my);

	testEmitter = App->psystem->AddEmiter(pos, 4, 2, 200, { 0.0f, 5.0f }, 300.0f, 100.0f, { 0, 0, 128, 128 });
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
		fPoint pos(mx, my);
		testEmitter->MoveEmitter(pos);
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN && testEmitter != nullptr)
	{
		testEmitter->StartEmission(5000.0f);
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT && testEmitter != nullptr)
	{
		fPoint newPos = testEmitter->GetEmitterPos();
		newPos.x += 5.0f;
		
		testEmitter->MoveEmitter(newPos);
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT && testEmitter != nullptr)
	{
		fPoint newPos = testEmitter->GetEmitterPos();
		newPos.x -= 5.0f;

		testEmitter->MoveEmitter(newPos);
	}
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT && testEmitter != nullptr)
	{
		fPoint newPos = testEmitter->GetEmitterPos();
		newPos.y -= 5.0f;

		testEmitter->MoveEmitter(newPos);
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && testEmitter != nullptr)
	{
		fPoint newPos = testEmitter->GetEmitterPos();
		newPos.y += 5.0f;

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


/* Things left TODO:

   1. Read attributes from an xml. When setting an emitter you say "fire" and read 
      from the xml the attributes. textureRect should not be in constructor anymore, 
	  just read form the xml file.

   2. Find out about blending modes.

   3. Improve random generator (bug in angles).

   4. Particle physics: movement equations + bezier + vortex turbulence.

   5. Color interpolation in particles.

   6. Emitters shapes.

   7. Emitters should be able to spawn other emitters.

   8. Emitters should be able to have a chain reaction, i.e: change its type and 
      then start spawning another types of particles. So it's like a chain of 
	  emissions. Fire, explosion, smoke in a loop for example.

   9. Remember that particle values should be floats no matter what. We don't want to
      lose precision when multiplying by dt. Then Blit() will ceil() them but that's 
	  okay as calculations will already be done.

  10. Once everything is set up try to do different types of particles an create a 
      unique atlas to store all the textures needed for each type of particle.

  11. Emission rate could be lower than 1.

  11. Clean code, add comments and test!

 */