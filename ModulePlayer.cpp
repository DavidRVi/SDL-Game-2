#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL.h"
#include "ModuleCollisions.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA
ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{
	position.x = 100;
	position.y = 216;

	// idle animation (arcade sprite sheet)
	idle.frames.push_back({7, 14, 60, 90});
	idle.frames.push_back({95, 15, 60, 89});
	idle.frames.push_back({184, 14, 60, 90});
	idle.frames.push_back({276, 11, 60, 93});
	idle.frames.push_back({366, 12, 60, 92});
	idle.speed = 0.2f;
	
	// walk backward animation (arcade sprite sheet)
	backward.frames.push_back({542, 131, 61, 87});
	backward.frames.push_back({628, 129, 59, 90});
	backward.frames.push_back({713, 128, 57, 90});
	backward.frames.push_back({797, 127, 57, 90});
	backward.frames.push_back({883, 128, 58, 91});
	backward.frames.push_back({974, 129, 57, 89});
	backward.speed = 0.1f;

	// TODO 8: setup the walk forward animation from ryu4.png
	forward.frames.push_back({ 9, 136, 65, 90 });
	forward.frames.push_back({ 78, 132, 65, 90});
	forward.frames.push_back({ 163, 129, 65, 90 });
	forward.frames.push_back({ 261, 129, 65, 90 });
	forward.frames.push_back({ 353, 129, 65, 90 });
	forward.frames.push_back({ 432, 129, 65, 90 });
	forward.speed = 0.1f;

	// TODO 20: HADOKEN ANIMATION
	hadoken.frames.push_back({ 493, 1563, 43, 32 });
	hadoken.frames.push_back({ 550, 1565, 56, 28 });
	hadoken.speed = 0.1f;

	playerCol = nullptr;
}

ModulePlayer::~ModulePlayer()
{
	// Homework : check for memory leaks
}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("ryu4.png"); // arcade version
	current_state = IDLE;
	playerCol = new Collider(position.x, position.y - 100, 60, 90, this, PLAYER);
	App->collisions->AddCollider(playerCol);
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	//playerCol->CleanUp();
	//playerCol = nullptr;
	App->textures->Unload(graphics);

	return true;
}

update_status ModulePlayer::PreUpdate() {
	current_state = IDLE;
	if (current_state == IDLE)
	{
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			//position.x++;
			current_state = FORWARD;
		}

		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			//position.x--;
			current_state = BACKWARD;
		}
	}
	else if (current_state == FORWARD) {
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_UP)
			current_state = IDLE;
	}
	else if (current_state == BACKWARD) {
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_UP)
			current_state = IDLE;
	}

	// HADOKEN
	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		_ParticleData hadokenData;
		hadokenData.tex = graphics;
		hadokenData.position.x = position.x + 50;
		hadokenData.position.y = position.y - 80;
		hadokenData.speed = fPoint(1.5, 0);
		hadokenData.anim = hadoken;

		Collider* hadokenCol = new Collider(hadokenData.position.x, hadokenData.position.y, 50, 30, this, PLAYERPARTICLE);
		App->particles->CreateParticle(hadokenData, hadokenCol);

		App->collisions->AddCollider(hadokenCol);
	}

	return UPDATE_CONTINUE;
}
// Update
update_status ModulePlayer::Update()
{
	// TODO 9: Draw the player with its animation
	// make sure to detect player movement and change its
	// position while cycling the animation(check Animation.h)
	
	switch (current_state)
	{
	case IDLE:
		App->renderer->Blit(graphics, position.x, position.y-100, &idle.GetCurrentFrame());
		break;
	case FORWARD:
		position.x++;
		App->renderer->Blit(graphics, position.x, position.y-100, &forward.GetCurrentFrame());
		break;
	case BACKWARD:
		position.x--;
		App->renderer->Blit(graphics, position.x, position.y-100, &backward.GetCurrentFrame());
		break;
	case FORWARD_WALL:
		App->renderer->Blit(graphics, position.x, position.y - 100, &forward.GetCurrentFrame());
		break;
	case BACKWARD_WALL:
		App->renderer->Blit(graphics, position.x, position.y - 100, &backward.GetCurrentFrame());
		break;
	}

	playerCol->SetPosition(position.x, position.y - 100);

	return UPDATE_CONTINUE;
}


update_status ModulePlayer::PostUpdate() {
	return UPDATE_CONTINUE;
}

bool ModulePlayer::OnCollisionEnter(Collider* a, Collider* b)
{
	if (b->getType() == WALL)
		LOG("ASDSA");
	return false;
}

bool ModulePlayer::OnCollisionStay(Collider* a, Collider* b) { 
	if (b->getType() == WALL)
	{
		if (current_state == FORWARD)
		{
			if (b->GetRect()->x >= position.x)
				current_state = FORWARD_WALL;
		}
		else if (current_state == BACKWARD)
		{
			if (b->GetRect()->x <= position.x)
				current_state = BACKWARD_WALL;
		}

		//LOG("COLLISIOON");
	}

	return false;
}

bool ModulePlayer::OnCollisionExit(Collider* a, Collider* b)
{

	if (b->getType() == WALL)
		LOG("ASDASD");
	/*
	_ParticleData hadokenData;
	hadokenData.tex = graphics;
	hadokenData.position.x = position.x + 50;
	hadokenData.position.y = position.y - 80;
	hadokenData.speed = fPoint(1.5, 0);
	hadokenData.anim = hadoken;

	Collider* hadokenCol = new Collider(hadokenData.position.x, hadokenData.position.y, 50, 30, this, PLAYERPARTICLE);
	App->particles->CreateParticle(hadokenData, hadokenCol);

	App->collisions->AddCollider(hadokenCol);
	*/
	return false;
}