#include "XennonGameWorld.h"
#include "GameObject.h"
#include "Sprite.h"
#include "StaticBackground.h"
#include "Pawn.h"
#include "Log.h"
#include "AnimationComponent.h"

Pawn* pawn;
void XennonGameWorld::Start()
{
	//StaticBackground* background = InstantiateObject<StaticBackground>();
	pawn = InstantiateObject<Pawn>();
	Sprite& sprite = pawn->AddComponent<Sprite>("drone.bmp", 8, 2, 1.f);
	pawn->AddComponent<AnimationComponent>(sprite, 8.f);
}

void XennonGameWorld::Update(float deltaTime)
{
	pawn->GetTransform()->GetPosition().x += 50 * deltaTime;
}
