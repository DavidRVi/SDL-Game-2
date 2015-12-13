#include "ModuleCollisions.h"

ModuleCollisions::ModuleCollisions(bool start_enabled) : Module(start_enabled) 
{
	_debug = false; 
}

ModuleCollisions::~ModuleCollisions() {

}

void ModuleCollisions::AddCollider(Collider* col) {
	colliderList.push_back(pair <Collider*, bool>(col, false));
}

bool ModuleCollisions::CleanUp() {
	for (ColliderList::iterator it = colliderList.begin(); it != colliderList.end(); ++it)
	{
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
					it->second = it->first->GetListener()->OnCollision(it->first, jt->first);
					jt->second = jt->first->GetListener()->OnCollision(jt->first, it->first);
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
			App->renderer->DrawRectangle(it->first->GetRect());
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
		if (it->second)
		{
			delete it->first;
			colliderList.erase(it++);
		}
		else it++;
	}

	return UPDATE_CONTINUE;
}

bool ModuleCollisions::DetectCollision(Collider* a, Collider* b) {
	return SDL_HasIntersection(a->GetRect(), b->GetRect());
}

void ModuleCollisions::setDebug(bool value) {
	_debug = value;
}
