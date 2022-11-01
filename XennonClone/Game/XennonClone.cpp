/*
* Client Game
************************************************************/
#include "CustomGameWorld.h"
#include "GameEngine.h"

int main(int argc, char** argv)
{
	GameEngine gameEngine;
	CustomGameWorld newWorld;
	gameEngine.Init("XennonClone - Powered by EngenhoIrrealXVII", 640, 480, &newWorld);
	gameEngine.StartAndRun();

	return 0;
}
