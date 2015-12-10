#include "Particle.h"
#include "Application.h"

Particle::Particle(_ParticleData data)
{
	pos = data.position;
	anim = data.anim;
	tex = data.tex;
	speed = data.speed;
}

fPoint Particle::getPos()
{
	return pos;
}
