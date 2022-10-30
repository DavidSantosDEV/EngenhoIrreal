#include "SDL.h"
#include "GameObject.h"
#include "Component.h"
#include <algorithm>
#include "Log.h"

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
}

void GameObject::AddComponent(std::shared_ptr<Component> componentToAdd)
{
	components.emplace_back(std::move(componentToAdd));
}
