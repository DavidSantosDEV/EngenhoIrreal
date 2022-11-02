/*
* Generic Component
************************************************************/

#include "GameWorld.h"
#include "GameEngine.h"
#include "GameObject.h"
#include "Component.h"
#include <algorithm>
#include "Log.h"

GameObject::GameObject() 
{
	LOG("BUILD");
}
GameObject::~GameObject() 
{
	GameEngine::GetGameWorld()->CallRemoveObjectFromStack(this);
	LOG("DESTROY");
}

void GameObject::Start()
{
	if (m_WasInitialized) { return; }

	LOG("GO Start");

	std::for_each(
		m_Components.begin(),
		m_Components.end(),
		[](std::shared_ptr<Component> cpt) { cpt->Start(); }
	);

	m_WasInitialized = true;
}

void GameObject::Update()
{
	//LOG("Update");
}
