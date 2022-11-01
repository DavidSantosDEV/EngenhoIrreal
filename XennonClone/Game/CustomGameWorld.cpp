#include "CustomGameWorld.h"
#include "Log.h"

void CustomGameWorld::Start()
{
	//InstatianteObject();
}

void CustomGameWorld::Update()
{
	if (bananas==8) {
		//InstatianteObject();
	}
	bananas++;
	LOG("Bananas " << bananas);
}
