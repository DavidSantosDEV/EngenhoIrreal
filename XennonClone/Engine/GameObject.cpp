/*
* Generic Component
************************************************************/

#include "SDL.h"
#include "GameObject.h"
#include "Component.h"
#include <algorithm>
#include "Log.h"

<<<<<<< Updated upstream
<<<<<<< Updated upstream
=======
=======
>>>>>>> Stashed changes
GameObject::GameObject() 
{
	LOG("BUILD");
}
GameObject::~GameObject() 
{
	GameEngine::GetGameWorld()->CallRemoveObjectFromStack(this);
	LOG("DESTROY");
}

>>>>>>> Stashed changes
void GameObject::Start()
{
	LOG("GO Start");

	std::for_each(
		components.begin(),
		components.end(),
		[](std::shared_ptr<Component> cpt) { cpt->Start(); }
	);
}

void GameObject::Update()
{
<<<<<<< Updated upstream
<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
=======

>>>>>>> Stashed changes
}

void GameObject::AddComponent(std::shared_ptr<Component> componentToAdd)
{
	components.emplace_back(std::move(componentToAdd));
}
