#include "InstanceCounter.h"
#include "Log.h"

int InstanceCounter::ComponentCount = 0;
int InstanceCounter::objectCount = 0;


void InstanceCounter::PrintCounts()
{
	LOG("Objects: " << objectCount << std::endl << "Components: " << ComponentCount);
}
