#include "XennonGameWorld.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Log.h"

void XennonGameWorld::Start()
{
	obj = InstantiateObject();
	obj->AddComponent<Sprite>();
	Sprite& render = obj->GetComponent<Sprite>();
	render.SetSpriteTexture("banana.png");
	render.SetSpriteScale(32, 32);
}

void XennonGameWorld::Update()
{
	static float x;
	static float y;
	obj->GetTransform()->SetPosition(x, y);
	x+=.1f;
	y+=.1f;
}
