/*
* Client Game
************************************************************/

#include "GameEngine.h"

int main(int argc, char** argv)
{
	GameEngine gameEngine;
	gameEngine.Init("XennonClone - Powered by EngenhoIrrealXVII", 640, 480);
	gameEngine.StartAndRun();
	return 0;
}
