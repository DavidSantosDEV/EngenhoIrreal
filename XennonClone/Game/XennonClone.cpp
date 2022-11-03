/*
* Client Game
************************************************************/
#include "XennonGameWorld.h"
#include "GameEngine.h"

int main(int argc, char** argv)
{
	GameEngine gameEngine;
	XennonGameWorld xennonGameWorld;
	gameEngine.Init("XennonClone - Powered by EngenhoIrrealXVII", 640, 480, &xennonGameWorld);
	gameEngine.StartAndRun();
	return 0;
}
