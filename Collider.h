#ifndef _COLLIDER_H_
#define _COLLIDER_H_

class Module;
struct SDL_Rect;

class Collider {
private:
	SDL_Rect* size;
	Module* listener = nullptr;

public:

};

#endif