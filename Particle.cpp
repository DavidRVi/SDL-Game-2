#include "Particle.h"
#include "Application.h"

Particle::Particle(_ParticleData data, float limit)
{
	pos = data.position;
	anim = data.anim;
	tex = data.tex;
	speed = data.speed;
	lifeTime = new Timer(limit);
	_isDirty = false;
}


Particle::~Particle()
{
	delete lifeTime;
}

fPoint Particle::getPos()
{
	return pos;
}

void Particle::Update()
{
	if (lifeTime->hasPassed())
		_isDirty = true;
	pos += speed;
}

Animation Particle::getAnimation() {
	return anim;
}

SDL_Texture* Particle::getText() {
	return tex;
}

SDL_Rect& Particle::GetCurrentFrame() {
	return anim.GetCurrentFrame();
}

bool Particle::isDirty() {
	return _isDirty;
}