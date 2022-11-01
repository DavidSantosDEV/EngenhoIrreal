/*
* Generic Component
************************************************************/

#include "GameWorld.h"
#include "GameEngine.h"
#include "GameObject.h"
#include "Component.h"
#include <algorithm>
#include "Log.h"

GameObject::GameObject() {
	LOG("BUILD");
}
GameObject::~GameObject() {
	GameEngine::GetGameWorld()->RemoveObject(this);
	LOG("DESTROY");
}

void GameObject::Start()
{
	LOG("GO Start");

	std::for_each(
		components.begin(),
		components.end(),
		[](std::shared_ptr<Component> cpt) { cpt->Start(); }
	);
	
	//if (World) {
	//	World->InstatianteObject();
	//}
	//GameEngine::GetInstance()->InstantiateObject();
}

void GameObject::Update()
{
	//LOG("Update");
}

void GameObject::AddComponent(std::shared_ptr<Component> componentToAdd)
{
	components.emplace_back(std::move(componentToAdd));
}
