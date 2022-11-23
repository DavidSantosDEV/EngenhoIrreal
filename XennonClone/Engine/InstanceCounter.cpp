/*
* - Used to check for Memory Leaks. Shows how many GO and 
* Components are currently in the game
************************************************************/

#include "InstanceCounter.h"
#include "Log.h"

int InstanceCounter::ComponentCount = 0;
int InstanceCounter::objectCount = 0;

void InstanceCounter::PrintCounts()
{
	LOG("Objects: " << objectCount << std::endl << "Components: " << ComponentCount);
}
