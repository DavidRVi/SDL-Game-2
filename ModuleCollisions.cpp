#include "ModuleCollisions.h"

ModuleCollisions::ModuleCollisions(bool start_enabled) : Module(start_enabled) 
{
	_debug = false; 
}

ModuleCollisions::~ModuleCollisions() {

}

void ModuleCollisions::AddCollider(Collider* col) {
	colliderList.push_back(pair <Collider*, Collision_status>(col, OUT));
}

bool ModuleCollisions::CleanUp() {
	for (ColliderList::iterator it = colliderList.begin(); it != colliderList.end(); ++it)
	{
		it->first->CleanUp();
		delete it->first;
	}
	colliderList.clear();
	return true;
}

update_status ModuleCollisions::PreUpdate() {
	if (!colliderList.empty())
	{
		ColliderList::iterator jt = colliderList.end();
		--jt;
		for (ColliderList::iterator it = colliderList.begin(); it != colliderList.end(); ++it)
		{
			for (; jt != it; --jt)
			{
				
				if (DetectCollision(it->first, jt->first))
				{
					switch (it->second)
					{
					case OUT:
						it->first->GetListener()->OnCollisionEnter(it->first, jt->first);
						jt->first->GetListener()->OnCollisionEnter(jt->first, it->first);
						it->second = ENTER;
						break;
					case STAY:
						it->first->GetListener()->OnCollisionStay(it->first, jt->first);
						jt->first->GetListener()->OnCollisionStay(jt->first, it->first);
						break;
					case ENTER:
						it->first->GetListener()->OnCollisionStay(it->first, jt->first);
						jt->first->GetListener()->OnCollisionStay(jt->first, it->first);
						it->second = STAY;
						break;
					case EXIT:
						it->first->GetListener()->OnCollisionEnter(it->first, jt->first);
						jt->first->GetListener()->OnCollisionEnter(jt->first, it->first);
						it->second = STAY;
						break;
					}
				}
				else {
					switch (it->second)
					{
					case ENTER:
						it->first->GetListener()->OnCollisionExit(it->first, jt->first);
						jt->first->GetListener()->OnCollisionExit(jt->first, it->first);
						it->second = EXIT;
						break;
					case STAY:
						it->first->GetListener()->OnCollisionExit(it->first, jt->first);
						jt->first->GetListener()->OnCollisionExit(jt->first, it->first);
						it->second = EXIT;
						break;
					case EXIT:
						it->second = OUT;
						break;
					}
				}

			}
			jt = colliderList.end();
			--jt;
		}
	}

	return UPDATE_CONTINUE;
}

update_status ModuleCollisions::Update() {
	if (_debug)
	{
		SDL_Surface* screen = App->window->screen_surface;
		Uint32 blue = SDL_MapRGB(screen->format, 0, 0, 255);
		SDL_SetRenderDrawColor(App->renderer->renderer, 0, 0, 255, 100);
		for (ColliderList::iterator it = colliderList.begin(); it != colliderList.end(); ++it)
		{
			if (it->first->getType() == WALL)
				SDL_SetRenderDrawColor(App->renderer->renderer, 255, 165, 0, 100);
			else if (it->first->getType() == PLAYER)
				SDL_SetRenderDrawColor(App->renderer->renderer, 0, 255, 0, 100);
			else if (it->first->getType() == PLAYERPARTICLE)
				SDL_SetRenderDrawColor(App->renderer->renderer, 0, 0, 255, 100);
			else if (it->first->getType() == ENEMY)
				SDL_SetRenderDrawColor(App->renderer->renderer, 255, 0, 0, 100);

			App->renderer->DrawRectangle(it->first->GetRect());
		}
			
	}

	if (App->input->GetKey(SDL_SCANCODE_B) == KEY_DOWN)
	{
		setDebug(!_debug);
	}

	return UPDATE_CONTINUE;
}

update_status ModuleCollisions::PostUpdate() {
	ColliderList::iterator it = colliderList.begin();
	while (it != colliderList.end()) {
		if (it->first->isDirty())
		{
			it->first->CleanUp();
			delete it->first;
			colliderList.erase(it++);
		}
		else it++;
	}

	return UPDATE_CONTINUE;

}

bool ModuleCollisions::DetectCollision(Collider* a, Collider* b) {
	bool _hasCollided = false;
	if (a->getType() != b->getType())
	{
		if (a->getType() == PLAYERPARTICLE || a->getType() == PLAYER)
		{
			if (b->getType() == PLAYERPARTICLE || b->getType() == PLAYER)
				_hasCollided = false;
			else _hasCollided = SDL_HasIntersection(a->GetRect(), b->GetRect());
		}
		else
			_hasCollided = SDL_HasIntersection(a->GetRect(), b->GetRect());
	}

	return _hasCollided;
}

void ModuleCollisions::setDebug(bool value) {
	_debug = value;
}
