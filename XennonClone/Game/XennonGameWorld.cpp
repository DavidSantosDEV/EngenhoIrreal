#include "XennonGameWorld.h"
#include "GameObject.h"
#include "Sprite.h"
#include "StaticBackground.h"
#include "Pawn.h"
#include "Log.h"
#include "AnimationComponent.h"
#include "Player.h"
#include "TestLayers.h"

Pawn* player;

void XennonGameWorld::Start()
{
	StaticBackground* background = InstantiateObject<StaticBackground>();
	StaticBackground* bg2 = InstantiateObject<StaticBackground>();
	player = InstantiateObject<Player>();

	InstantiateObject<TestLayers>();
}

void XennonGameWorld::Update(float deltaTime)
{
	//player->GetTransform()->GetPosition().x += 50 * deltaTime;
}
