#include "Particle.h"
#include "Application.h"
#include "Collider.h"

Particle::Particle(_ParticleData data, Collider* aCol, float limit)
{
	pos = data.position;
	anim = data.anim;
	tex = data.tex;
	speed = data.speed;
	lifeTime = new Timer(limit);
	_isDirty = false;

	particleCol = aCol;
}


Particle::~Particle()
{
	//CleanUp();
}

fPoint Particle::getPos()
{
	return pos;
}

void Particle::Update()
{
	if (lifeTime->hasPassed())
	{
		_isDirty = true;
		particleCol->SetDirty(true);
	}

	pos += speed;
	particleCol->SetPosition(pos.x, pos.y);
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

void Particle::CleanUp() {
	RELEASE(lifeTime);
	//particleCol->SetDirty(true);
	//particleCol = nullptr;
}