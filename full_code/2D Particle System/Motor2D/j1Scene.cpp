#include "j1App.h"
#include "j1Input.h"
#include "j1Scene.h"
#include "j1Render.h"
#include "j1Textures.h"
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
	torchTex = App->tex->Load("textures/torch.png");
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
		fPoint pos((float)mx,(float)my);
		pos.y -= 230.0f;
		eFire = App->psystem->AddEmiter(pos, EmitterType::EMITTER_TYPE_FIRE);
	}

	int mx, my;
	App->input->GetMousePosition(mx, my);
	fPoint pos((float)mx, (float)my);

	App->render->Blit(torchTex, pos.x - 43, pos.y - 270, &rect);

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

	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN && eFlame != nullptr)
		eFlame->VortexSensitive(false);
	
	if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN && eFlame != nullptr)
		eFlame->VortexSensitive(true);

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
		eSmoke = App->psystem->AddEmiter(pos, EmitterType::EMITTER_TYPE_SMOKE);
	}

	if (App->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN)
	{
		int mx, my;
		App->input->GetMousePosition(mx, my);
		fPoint pos((float)mx, (float)my);
		eSpark = App->psystem->AddEmiter(pos, EmitterType::EMITTER_TYPE_SPARK);
	}

	if (App->input->GetKey(SDL_SCANCODE_8) == KEY_DOWN)
	{
		int mx, my;
		App->input->GetMousePosition(mx, my);
		fPoint pos((float)mx, (float)my);
		ePixelSmoke = App->psystem->AddEmiter(pos, EmitterType::EMITTER_TYPE_PIXEL_SMOKE);
	}

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		App->psystem->RemoveAllEmitters();
	}

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN && eFire != nullptr)
	{
		eFire->StopEmission(5000.0f);
	}

	if (eFire != nullptr )
	{
		int mx, my;
		App->input->GetMousePosition(mx, my);
		fPoint pos((float)mx, (float)my);
		pos.y -= 230.0f;
		eFire->MoveEmitter(pos);
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN && eFire != nullptr)
	{
		eFire->StartEmission(5000.0f);
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
	eSmoke = nullptr;
	eFlame = nullptr;
	eWave_1 = nullptr;
	eWave_2 = nullptr;
	eBurst_1 = nullptr;
	eBurst_2 = nullptr;
	eBubbles = nullptr;
	eSpark = nullptr;
	ePixelSmoke = nullptr;

	App->tex->UnLoad(torchTex);
	torchTex = nullptr;

	return true;
}

// TODOs:

// - Separate Update and Draw methods to have more error control (revise particlePool update, returns three possible values and it's not very nice, 
//   maybe return enums or separate draw and update). 
// - Add animations

//   CUBIC BEZIER CURVES!--------------------------------------------------------------------------------------------------------------------------
// - Add cubic bezier curve to particles' speed in psystem_config.xml, maybe something along these lines:
//	 <cubicBezier handleAx = "1" handleAy = "1" handleBx = "1" handleBy = "1"/>
//	 In case startSpeed is not 0 or endSpeed is not 0 (and they both are different) then we would need to do some workarounds. NOTE: figure out how 
//   to solve this issue. One potential solution might be:
//   Case startSpeed < endSpeed:
//		- Current particle speed = startSpeed + (endSpeed - startSpeed) * BezierValue (between -1 and 1)
//   Case startSpeed > endSpeed:
//		- Current particle speed = startSpeed - abs(endSpeed - startSpeed) * BezierValue (between -1 and 1)
//   Case startSpeed = endSpeed:
//		- Current particle speed = startSpeed (no calculations are performed)
//   Case where Bezier curve is linear (see http://cubic-bezier.com):
//      - Linear interpolation between startSpeed and endSpeed is applied
//	 NOTE: control cases where bezier user input values exceeds 1 or -1 limits (if it's > 1 then it's 1, and if it's < -1 then it's -1).
//   ----------------------------------------------------------------------------------------------------------------------------------------------

// - When calling remove and removeAll delete particles when all particles have died. Not instantly. Maybe create tow new special methods for that.
// - Try doing particle pixel-type effects.
// - Change name of modules and files and folders (j1 is not nice).
// - Make a new branch with th good version maybe.
// - Prewarm options.
// - Add a boolean so particles can react or not to vortex. Check Project II to see how it's done. But do it through xml, cleaner.
// - Other improvements (see web).
// - Solve warnings