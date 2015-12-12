#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include "SDL/include/SDL.h"
class Module;
struct SDL_Rect;

class Collider {
private:
	SDL_Rect* size;
	const Module* listener = nullptr;

public:

	Collider(int x, int y, int w, int h, const Module* listener)
	{
		size = new SDL_Rect();
		size->x = x;
		size->y = y;
		size->w = w;
		size->h = h;

		this->listener = listener;
	}

	~Collider() {
		delete size;
		size = nullptr;
		listener = nullptr;
	}

	SDL_Rect* GetRect(){
		return size;
	}

	const Module* GetListener() {
		return listener;
	}
};

#endif