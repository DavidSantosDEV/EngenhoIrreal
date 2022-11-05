#include "XennonGameWorld.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "Pawn.h"
#include "Log.h"

void XennonGameWorld::Start()
{
	Pawn* pawn = InstantiateObject<Pawn>();
	pawn->AddComponent<RenderComponent>();
	RenderComponent& render = pawn->GetComponent<RenderComponent>();
}

void XennonGameWorld::Update(float deltaTime)
{
}
