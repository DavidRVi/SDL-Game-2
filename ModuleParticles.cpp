#include "ModuleParticles.h"
#include "Application.h"
#include "ModuleRender.h"

ModuleParticles::ModuleParticles()
{
}

bool ModuleParticles::Start()
{
	LOG("Starting particles");

	return true;
}

void ModuleParticles::CreateParticle(_ParticleData particleData)
{
	Particle *p = new Particle(particleData, 3000);
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

update_status ModuleParticles::PostUpdate()
{
	list<Particle*>::iterator it = particles.begin();
	while (it != particles.end()) {
		if ((*it)->isDirty())
		{
			delete *it;
			particles.erase(it++);
		}
		else it++;
	}

	return UPDATE_CONTINUE;
}

bool ModuleParticles::CleanUp()
{
	for (list<Particle*>::iterator it = particles.begin(); it != particles.end(); ++it)
	{
		delete *it;
	}
	particles.clear();
	return true;
}

ModuleParticles::~ModuleParticles()
{
}