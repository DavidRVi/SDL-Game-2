#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include "SDL/include/SDL.h"
class Module;
struct SDL_Rect;

enum colliderType { PLAYER = 0, ENEMY, WALL, ENEMYPARTICLE, PLAYERPARTICLE };
class Collider {
private:
	SDL_Rect* size;
	Module* listener = nullptr;
	colliderType type;

public:

	Collider(int x, int y, int w, int h, Module* listener, colliderType aType)
	{
		size = new SDL_Rect();
		size->x = x;
		size->y = y;
		size->w = w;
		size->h = h;
		type = aType;
		this->listener = listener;
	}

	Collider(SDL_Rect* rect, Module* listener, colliderType aType)
	{
		size = rect;
		this->listener = listener;
		type = aType;
	}

	~Collider() {
		delete size;
		size = nullptr;
		listener = nullptr;
	}

	SDL_Rect* GetRect(){
		return size;
	}

	Module* GetListener() {
		return listener;
	}
};

#endif