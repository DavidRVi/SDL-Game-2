#ifndef __MODULE_H__
#define __MODULE_H__
#include "Globals.h"

class Collider;

class Application;

class Module
{
public:

	Module(bool active = true) : active(active)
	{}

	virtual ~Module()
	{}

	bool IsEnabled() const
	{
		return active;
	}

	 bool Enable()
	{
		if(active == false)
			return active = Start();

		return true;
	}

	 bool Disable()
	 {
		 if(active == true)
			 return active = !CleanUp();

		 return true;
	 }

	virtual bool Init() 
	{
		return true; 
	}

	virtual bool Start()
	{
		return true;
	}

	virtual update_status PreUpdate()
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status Update()
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status PostUpdate()
	{
		return UPDATE_CONTINUE;
	}

	virtual bool CleanUp() 
	{ 
		return true; 
	}

	virtual bool OnCollisionEnter(Collider* a, Collider* b){ return false; };		//Returns true if a needs to be deleted
	virtual bool OnCollisionStay(Collider* a, Collider* b) { return false; };
	virtual bool OnCollisionExit(Collider* a, Collider* b) { return false; };

private:
	bool active = true;
};

#endif // __MODULE_H__