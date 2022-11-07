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
	AnimationComponent& anim = pawn->AddComponent<AnimationComponent>(sprite, false, 8.f);
	anim.PlayAnimation(1, 1, 1, 7);
}

void XennonGameWorld::Update(float deltaTime)
{
	pawn->GetTransform()->GetPosition().x += 50 * deltaTime;
}
