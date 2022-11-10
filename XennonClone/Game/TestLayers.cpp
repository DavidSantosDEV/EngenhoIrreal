#include "TestLayers.h"
#include "Sprite.h"

TestLayers::TestLayers() : GameObject()
{
	AddComponent<Sprite>("drone.bmp", 8, 2, 4.f, -5);
}
