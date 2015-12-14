#ifndef __MODULESCENEKEN_H__
#define __MODULESCENEKEN_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;
class Collider;

class ModuleSceneKen : public Module
{
public:
	ModuleSceneKen( bool start_enabled = true);
	~ModuleSceneKen();

	bool Start();
	update_status Update();
	//update_status PostUpdate();
	bool CleanUp();

public:
	
	SDL_Texture* graphics = nullptr;
	SDL_Rect ground;
	SDL_Rect background;
	SDL_Rect foreground;
	Animation flag;
	Animation girl;

private:
	float t_ship;
	bool ship_state;
	float ship_offset;

	Collider* ground_wall;
	Collider* left_wall;
	Collider* right_wall;
};

#endif // __MODULESCENEKEN_H__