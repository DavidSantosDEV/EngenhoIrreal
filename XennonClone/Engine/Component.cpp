/*
* Generic Component. Start() and Update() are automatically.
* Start() On AddComponent and Update() on Engine Loop
************************************************************/

#include "Component.h"
#include "Log.h"

void Component::Start()
{
	LOG("Component Start");
}

void Component::Update(float deltaSeconds)
{
	//LOG("Component Update");
}
