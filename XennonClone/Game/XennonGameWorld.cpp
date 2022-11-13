#include "XennonGameWorld.h"
#include "GameObject.h"
#include "Sprite.h"
#include "StaticBackground.h"
#include "Pawn.h"
#include "Log.h"
#include "AnimationComponent.h"
#include "Player.h"
#include "RocksBackground.h"


void XennonGameWorld::Start()
{
	StaticBackground* background = InstantiateObject<StaticBackground>();
	InstantiateObject<RocksBackground>();
	InstantiateObject<Player>();
}

void XennonGameWorld::Update(float deltaTime)
{
	//player->GetTransform()->GetPosition().x += 50 * deltaTime;
}
