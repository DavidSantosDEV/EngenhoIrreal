/*
* Client Game
************************************************************/
<<<<<<< Updated upstream
<<<<<<< Updated upstream

=======
#include "XennonGameWorld.h"
>>>>>>> Stashed changes
=======
#include "XennonGameWorld.h"
>>>>>>> Stashed changes
#include "GameEngine.h"

int main(int argc, char** argv)
{
	GameEngine gameEngine;
<<<<<<< Updated upstream
<<<<<<< Updated upstream
	gameEngine.Init("XennonClone - Powered by EngenhoIrrealXVII", 640, 480);
=======
=======
>>>>>>> Stashed changes
	XennonGameWorld newWorld;
	gameEngine.Init("XennonClone - Powered by EngenhoIrrealXVII", 640, 480, &newWorld);
>>>>>>> Stashed changes
	gameEngine.StartAndRun();

	return 0;
}
