#include "StaticBackground.h"
#include "Sprite.h"
#include "GameEngine.h"

StaticBackground::StaticBackground() : GameObject() 
{
	m_SpriteComponent = AddComponent<Sprite>("galaxy2.bmp", -2);
}

StaticBackground::~StaticBackground()
{
	delete m_SpriteComponent;
}