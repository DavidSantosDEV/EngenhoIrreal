#include "XennonGameWorld.h"
#include "GameObject.h"
#include "Sprite.h"
#include "StaticBackground.h"
#include "Pawn.h"
#include "Log.h"
#include "AnimationComponent.h"
#include "Player.h"
#include "Rusher.h"
#include "PhysicsComponent.h"
#include "EnemyManager.h"
#include "RocksBackground.h"
#include "Loner.h"

void XennonGameWorld::Start()
{
	//InstantiateObject<EnemyManager>();
	StaticBackground* background = InstantiateObject<StaticBackground>();
	InstantiateObject<RocksBackground>();
	GameObject* p = InstantiateObject<Player>();
	p->GetComponent<PhysicsComponent>()->SetPosition(Vector2D(250, 300));
	InstantiateObject<Rusher>()->GetComponent<PhysicsComponent>()->SetPosition(Vector2D(300, -300));
	InstantiateObject<Loner>()->GetComponent<PhysicsComponent>()->SetPosition(Vector2D(800, 300));
}

void XennonGameWorld::Update(float deltaTime)
{
}
