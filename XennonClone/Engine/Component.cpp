/*
* Generic Component. Start() and Update() are automatically called
* from m_OwnerGameObject
************************************************************/

#include "Component.h"
#include "Log.h"

void Component::Start()
{
	LOG("Component Start");
}

void Component::Update(float deltaSeconds)
{
	LOG("Component Update");
}
