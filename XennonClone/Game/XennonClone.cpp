/*
* Client Game
************************************************************/
<<<<<<< Updated upstream

=======
#include "XennonGameWorld.h"
>>>>>>> Stashed changes
#include "GameEngine.h"

int main(int argc, char** argv)
{
	GameEngine gameEngine;
<<<<<<< Updated upstream
	gameEngine.Init("XennonClone - Powered by EngenhoIrrealXVII", 640, 480);
=======
	XennonGameWorld newWorld;
	gameEngine.Init("XennonClone - Powered by EngenhoIrrealXVII", 640, 480, &newWorld);
>>>>>>> Stashed changes
	gameEngine.StartAndRun();

	return 0;
}
