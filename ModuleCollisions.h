#ifndef __MODULECOLLISIONS_H_
#define __MODULECOLLISIONS_H_

#include "Module.h"
#include "Collider.h"
#include <list>
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleRender.h"


enum Collision_status {ENTER = 0, STAY, EXIT, OUT };

typedef std::list<pair<Collider*, Collision_status>> ColliderList;
class ModuleCollisions : public Module {
public:
	ModuleCollisions(bool start_enabled = true);
	~ModuleCollisions();

	void AddCollider(Collider* col);

	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();

	bool CleanUp();
	void setDebug(bool value);

private:

	ColliderList colliderList;
	bool _debug;

	bool DetectCollision(Collider* a, Collider* b);

};

#endif