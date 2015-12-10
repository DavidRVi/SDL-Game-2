#ifndef __MODULEPARTICLES_H_
#define __MODULEPARTICLES_H_

#include "Module.h"
#include "Globals.h"
#include "Particle.h"
#include <list>

struct SDL_Texture;

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();

	void CreateParticle(_ParticleData particleData);


private:
	std::list<Particle*> particles;

};

#endif