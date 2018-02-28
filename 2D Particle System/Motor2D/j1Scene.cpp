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
	int randSpeed = rand() % (50 - 200 + 1) + 50;
	int randAngle = rand() % (0 - 360 + 1) + 0;
	int randLife = 50;
	int randRadius = rand() % (5 - 25 + 1) + 5;
	
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		int mx, my;
		App->input->GetMousePosition(mx, my);
		iPoint pos(mx, my);

		emitters_list.push_back(new Emitter(pos, randAngle, randSpeed));
 	}

	if (!emitters_list.empty())
	{
		std::list<Emitter*>::reverse_iterator it;
		for (it = emitters_list.rbegin(); it != emitters_list.rend(); ++it)
		{
			(*it)->Update(dt);
		}
	}

	//TODO: find a way to control emission rate
	/*testParticle.Generate({ 500, 500 }, randSpeed, randAngle, randRadius, randLife);

	testParticle.Update(dt);*/
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	std::list<Emitter*>::reverse_iterator it;
	for (it = emitters_list.rbegin(); it != emitters_list.rend(); ++it)
	{
		delete (*it);
	}

	return true;
}