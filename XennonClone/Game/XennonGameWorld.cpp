#include "XennonGameWorld.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "Pawn.h"
#include "Log.h"

void XennonGameWorld::Start()
{
	Pawn* gameObject = InstantiateObject<Pawn>();
	gameObject->AddComponent<RenderComponent>();
	RenderComponent& render = gameObject->GetComponent<RenderComponent>();
	delete gameObject;
}

void XennonGameWorld::Update(float deltaTime)
{
}
