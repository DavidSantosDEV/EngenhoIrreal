#include "XennonGameWorld.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Log.h"

void XennonGameWorld::Start()
{
	GameObject* gameObject = InstantiateObject();
	gameObject->AddComponent<Sprite>();
	Sprite& render = gameObject->GetComponent<Sprite>();
}

void XennonGameWorld::Update()
{
}
