#pragma once
#include "Globals.h"

struct SDL_Texture;

class Particle
{
private:

	fPoint pos;
	Animation anim;
	SDL_Texture* tex;
	fPoint speed;

public: 
	Particle(_ParticleData data);

	fPoint getPos();

	void Update()
	{
		pos += speed;
	}

	Animation getAnimation()
	{
		return anim;
	}

	SDL_Texture* getText()
	{
		return tex;
	}

	SDL_Rect& GetCurrentFrame()
	{
		return anim.GetCurrentFrame();
	}
};