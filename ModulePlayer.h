#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"

struct SDL_Texture;
class Collider;

enum state { IDLE, FORWARD, FORWARD_WALL, BACKWARD, BACKWARD_WALL };
class ModulePlayer : public Module
{
public:
	ModulePlayer(bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	bool OnCollisionEnter(Collider* a, Collider* b);
	bool OnCollisionStay(Collider* a, Collider* b);
	bool OnCollisionExit(Collider* a, Collider* b);


public:

	SDL_Texture* graphics = nullptr;
	Animation idle;
	Animation backward;
	Animation forward;

	Animation hadoken;
	iPoint position;

private:
	state current_state;
	Collider* playerCol;
};

#endif // __MODULEPLAYER_H__