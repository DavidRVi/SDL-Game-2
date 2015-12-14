#ifndef __PARTICLE_H_
#define __PARTICLE_H_

#include "Globals.h"
#include "Timer.h"

struct SDL_Texture;
class Collider;

class Particle
{
private:

	fPoint pos;
	Animation anim;
	SDL_Texture* tex;
	fPoint speed;
	Timer* lifeTime;
	bool _isDirty;

	Collider* particleCol;

public: 
	Particle(_ParticleData data, Collider* aCol, float limit = 1000);
	~Particle();

	fPoint getPos();

	void Update();
	void CleanUp();
	Animation getAnimation();
	SDL_Texture* getText();
	SDL_Rect& GetCurrentFrame();
	bool isDirty();
};

#endif