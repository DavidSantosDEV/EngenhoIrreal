#include "XennonGameWorld.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Pawn.h"
#include "Log.h"

void XennonGameWorld::Start()
{
	Pawn* gameObject = InstantiateObject<Pawn>();
	gameObject->AddComponent<Sprite>();
	Sprite& render = gameObject->GetComponent<Sprite>();
	render.SetSpriteTexture("banana.png");
	render.SetSpriteScale(32, 32);
}

void XennonGameWorld::Update(float deltaTime)
{
	
}
