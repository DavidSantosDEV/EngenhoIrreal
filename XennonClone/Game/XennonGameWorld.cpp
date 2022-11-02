#include "XennonGameWorld.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "Log.h"

void XennonGameWorld::Start()
{
	GameObject* gameObject = InstantiateObject();
	gameObject->AddComponent<RenderComponent>();
	RenderComponent& render = gameObject->GetComponent<RenderComponent>();
}

void XennonGameWorld::Update()
{
}
