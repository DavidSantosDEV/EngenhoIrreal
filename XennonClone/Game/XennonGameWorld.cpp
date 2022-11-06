#include "XennonGameWorld.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Pawn.h"
#include "Log.h"

void XennonGameWorld::Start()
{
	Pawn* pawn = InstantiateObject<Pawn>();
	pawn->AddComponent<Sprite>("banana.png", 32.f, 32.f);

	Vector2D v(1, 4);
	Vector2D v2(2, 6);

	v + v2;
	LOG(v.x);
}

void XennonGameWorld::Update(float deltaTime)
{
	
}
