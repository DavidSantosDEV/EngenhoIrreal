#include "RocksBackground.h"
#include "Sprite.h"
#include "ParallaxComponent.h"

RocksBackground::RocksBackground() : GameObject()
{
	m_SpriteComponent = AddComponent<Sprite>("background2.bmp", -1);

	AddComponent<ParallaxComponent>()->SetSpeed(70.f);
}

RocksBackground::~RocksBackground()
{
	delete m_SpriteComponent;
}
