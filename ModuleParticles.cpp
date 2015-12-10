#include "ModuleParticles.h"
#include "Application.h"
#include "ModuleRender.h"

ModuleParticles::ModuleParticles()
{
}

bool ModuleParticles::Start()
{
	LOG("Loading particles");

	return true;
}

void ModuleParticles::CreateParticle(_ParticleData particleData)
{
	Particle *p = new Particle(particleData);
	particles.push_back(p);
}

update_status ModuleParticles::Update()
{
	for (list<Particle*>::iterator it = particles.begin(); it != particles.end(); ++it)
	{
		(*it)->Update();
		App->renderer->Blit((*it)->getText(), (*it)->getPos().x, (*it)->getPos().y, &(*it)->GetCurrentFrame());
	}

	return UPDATE_CONTINUE;
}

bool ModuleParticles::CleanUp()
{
	return true;
}

ModuleParticles::~ModuleParticles()
{
}