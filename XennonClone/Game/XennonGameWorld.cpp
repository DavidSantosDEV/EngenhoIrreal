#include "XennonGameWorld.h"
#include "GameObject.h"
#include "Sprite.h"
#include "StaticBackground.h"
#include "Pawn.h"
#include "Log.h"
#include "PhysicsTestActor.h"
#include <string>
#include "AnimationComponent.h"
#include "Player.h"
#include "RocksBackground.h"

Pawn* player;
GameObject* pawn;

void XennonGameWorld::Start()
{
	StaticBackground* background = InstantiateObject<StaticBackground>();
	InstantiateObject<RocksBackground>();
	player = InstantiateObject<Player>();
	//StaticBackground* background = InstantiateObject<StaticBackground>();
	pawn = InstantiateObject<GameObject>();
	pawn->name = "pawn";
	Sprite* sprite = pawn->AddComponent<Sprite>("drone.bmp", 8, 2, 1.f);
	AnimationComponent* anim = pawn->AddComponent<AnimationComponent>(sprite, false, 8.f);
	anim->PlayAnimation(1, 1, 1, 7);

	PhysicsTestActor* ob = InstantiateObject<PhysicsTestActor>();
	ob->name = "Ob";
	GameObject* test = InstantiateObject<PhysicsTestActor>();
	test->GetComponent<PhysicsComponent>()->SetPosition(Vector2D(300, -100));
	test->GetComponent<PhysicsComponent>()->SetGravityScale(0);
	test->name = "test";
	ob->SetHasInput();
	ob->GetComponent<PhysicsComponent>()->SetPosition(Vector2D(300, -300));
}

void XennonGameWorld::Update(float deltaTime)
{
	//player->GetTransform()->GetPosition().x += 50 * deltaTime;
}
