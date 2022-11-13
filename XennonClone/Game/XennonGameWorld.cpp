#include "XennonGameWorld.h"
#include "StaticBackground.h"
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
