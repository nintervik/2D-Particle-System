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
		eSmoke_1 = App->psystem->AddEmiter(pos, EmitterType::EMITTER_TYPE_SMOKE_1);
	}

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		int mx, my;
		App->input->GetMousePosition(mx, my);
		fPoint pos((float)mx, (float)my);
		eWave_1 = App->psystem->AddEmiter(pos, EmitterType::EMITTER_TYPE_WAVE_1);
		eBurst_1 = App->psystem->AddEmiter(pos, EmitterType::EMITTER_TYPE_BURST);
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

	if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
	{
		int mx, my;
		App->input->GetMousePosition(mx, my);
		fPoint pos((float)mx, (float)my);
		eWave_2 = App->psystem->AddEmiter(pos, EmitterType::EMITTER_TYPE_WAVE_2);
		eBurst_2 = App->psystem->AddEmiter(pos, EmitterType::EMITTER_TYPE_BURST);
	}

	if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN)
	{
		int mx, my;
		App->input->GetMousePosition(mx, my);
		fPoint pos((float)mx, (float)my);
		eSmoke_2 = App->psystem->AddEmiter(pos, EmitterType::EMITTER_TYPE_SMOKE_2);
	}

	if (App->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN)
	{
		int mx, my;
		App->input->GetMousePosition(mx, my);
		fPoint pos((float)mx, (float)my);
		eSpark = App->psystem->AddEmiter(pos, EmitterType::EMITTER_TYPE_SPARK);
	}

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		App->psystem->RemoveAllEmitters();
	}

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN && eFire != nullptr)
	{
		eFire->StopEmission(5000.0f);
	}

	if (eSmoke_2 != nullptr )
	{
		int mx, my;
		App->input->GetMousePosition(mx, my);
		fPoint pos((float)mx, (float)my);
		eSmoke_2->MoveEmitter(pos);
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN && eFire != nullptr)
	{
		eFire->StartEmission(5000.0f);
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT && eSmoke_1 != nullptr)
	{
		fPoint newPos = eSmoke_1->GetEmitterPos();
		newPos.x += 5.0f;
		
		eSmoke_1->MoveEmitter(newPos);
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT && eSmoke_1 != nullptr)
	{
		fPoint newPos = eSmoke_1->GetEmitterPos();
		newPos.x -= 5.0f;

		eSmoke_1->MoveEmitter(newPos);
	}
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT && eSmoke_1 != nullptr)
	{
		fPoint newPos = eSmoke_1->GetEmitterPos();
		newPos.y -= 5.0f;

		eSmoke_1->MoveEmitter(newPos);
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && eSmoke_1 != nullptr)
	{
		fPoint newPos = eSmoke_1->GetEmitterPos();
		newPos.y += 5.0f;

		eSmoke_1->MoveEmitter(newPos);
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

	eFire = nullptr;
	eSmoke_1 = nullptr;
	eSmoke_2 = nullptr;
	eFlame = nullptr;
	eWave_1 = nullptr;
	eWave_2 = nullptr;
	eBurst_1 = nullptr;
	eBurst_2 = nullptr;
	eBubbles = nullptr;
	eSpark = nullptr;

	return true;
}