#include "ModuleCollisions.h"

ModuleCollisions::ModuleCollisions(bool start_enabled) : Module(start_enabled) 
{ }

ModuleCollisions::~ModuleCollisions() {

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
	ColliderList::iterator jt = colliderList.end();
	--jt;
	for (ColliderList::iterator it = colliderList.begin(); it != colliderList.end(); ++it)
	{
		for (; jt != it; --jt)
		{
			if (DetectCollision(it->first, jt->first))
			{
				it->first->GetListener()->OnCollision(it->first, jt->first);
				jt->first->GetListener()->OnCollision(jt->first, it->first);
			}
		}
		jt = colliderList.end();
		--jt;
	}

	return UPDATE_CONTINUE;
}

bool ModuleCollisions::DetectCollision(Collider* a, Collider* b) {
	return SDL_HasIntersection(a->GetRect(), b->GetRect());
}