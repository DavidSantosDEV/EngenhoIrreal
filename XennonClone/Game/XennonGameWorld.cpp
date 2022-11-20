#include "XennonGameWorld.h"
#include "GameObject.h"
#include "Sprite.h"
#include "StaticBackground.h"
#include "Pawn.h"
#include "Log.h"
#include "AnimationComponent.h"
#include "Player.h"
#include "Enemy.h"
#include "PhysicsComponent.h"
#include "EnemyManager.h"
#include "RocksBackground.h"

void XennonGameWorld::Start()
{
	InstantiateObject<EnemyManager>();
	StaticBackground* background = InstantiateObject<StaticBackground>();
	InstantiateObject<RocksBackground>();
	GameObject* p = InstantiateObject<Player>();
	p->GetComponent<PhysicsComponent>()->SetPosition(Vector2D(120, 50));
	InstantiateObject<Enemy>();
}

void XennonGameWorld::Update(float deltaTime)
{
	//player->GetTransform()->GetPosition().x += 50 * deltaTime;
}
