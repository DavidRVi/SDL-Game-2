#pragma once
#include "Globals.h"
#include "Timer.h"
struct SDL_Texture;

class Particle
{
private:

	fPoint pos;
	Animation anim;
	SDL_Texture* tex;
	fPoint speed;
	Timer* lifeTime;
	bool _isDirty;

public: 
	Particle(_ParticleData data, float limit = 1000);
	~Particle();

	fPoint getPos();

	void Update();
	Animation getAnimation();
	SDL_Texture* getText();
	SDL_Rect& GetCurrentFrame();
	bool isDirty();
};