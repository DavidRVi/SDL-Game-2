#include "Globals.h"
#include "Application.h"
#include "ModuleSceneKen.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneKen::ModuleSceneKen(bool start_enabled) : Module(start_enabled)
{
	// ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;

	// TODO 2 : setup the foreground (PINK ship) with
	// coordinates x,y,w,h from ken_stage.png
	foreground.x = 8;
	foreground.y = 24;
	foreground.w = 521;
	foreground.h = 176;
	
	// Background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;

	// flag animation
	flag.frames.push_back({848, 208, 40, 40});
	flag.frames.push_back({848, 256, 40, 40});
	flag.frames.push_back({848, 304, 40, 40});
	flag.speed = 0.08f;

	// TODO 4: Setup Girl Animation from coordinates from ken_stage.png
	girl.frames.push_back({ 624, 16, 31, 55 });
	girl.frames.push_back({ 624, 80, 31, 55 });
	girl.frames.push_back({ 624, 144, 31, 55 });
	girl.frames.push_back({ 624, 80, 31, 55 });
	girl.speed = 0.03f;

}

ModuleSceneKen::~ModuleSceneKen()
{}

// Load assets
bool ModuleSceneKen::Start()
{
	LOG("Loading ken scene");
	
	graphics = App->textures->Load("ken_stage.png");

	// TODO 7: Enable the player module
	App->player->Enable();
	// TODO 0: trigger background music
	App->audio->PlayMusic(KEN_MUSIC);
	t_ship = SDL_GetTicks();
	ship_state = false;
	ship_offset = 0;
	return true;
}

// UnLoad assets
bool ModuleSceneKen::CleanUp()
{
	LOG("Unloading ken scene");

	App->textures->Unload(graphics);
	App->player->Disable();
	
	return true;
}

// Update: draw background
update_status ModuleSceneKen::Update()
{
	// TODO 5: make sure the ship goes up and down DONE

	// Draw everything --------------------------------------
	// TODO 1: Tweak the movement speed of the sea&sky + flag to your taste
	App->renderer->Blit(graphics, 0, 0, &background, .75f); // sea and sky
	App->renderer->Blit(graphics, 560, 8, &(flag.GetCurrentFrame()), .75f); // flag animation
	float current = SDL_GetTicks();
	// TODO 3: Draw the ship. Be sure to tweak the speed.
	App->renderer->Blit(graphics, 0, 0, &foreground, .90f);
	SDL_Rect girlFrame = girl.GetCurrentFrame();
	girlFrame.y += ship_offset;
	App->renderer->Blit(graphics, 192, 104, &girlFrame, .90f);
	
	
	
	if (current - t_ship >= 1000)
	{
		if (ship_state)
		{
			if (foreground.y >= 24)
			{
				ship_offset--;
				foreground.y--;
			}
		else ship_state = false;
		}
		else if (foreground.y <= 28)
		{
			foreground.y++;
			ship_offset++;
		}
		else ship_state = true;
		t_ship = SDL_GetTicks();
	}

	// TODO 6: Draw the girl. Make sure it follows the ship movement! DONE
	
	App->renderer->Blit(graphics, 0, 170, &ground);

	// TODO 10: Build an entire new scene "honda", you can find its
	// and music in the Game/ folder


	// TODO 11: Make that pressing space triggers a switch to honda logic module
	// using FadeToBlack module

	return UPDATE_CONTINUE;
}