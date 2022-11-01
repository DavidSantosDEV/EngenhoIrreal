#include "CustomGameWorld.h"
#include "Log.h"


#include "Ship.h"
void CustomGameWorld::Start()
{
	InstantiateObject();
	//
}

void CustomGameWorld::Update()
{
	GameObject* obj = InstantiateObject();
	delete obj;
	bananas++;
	LOG("Bananas " << bananas);
}
