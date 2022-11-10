#include "StaticBackground.h"
#include "Sprite.h"
#include "GameEngine.h"

StaticBackground::StaticBackground() : GameObject() 
{
	m_SpriteComponent = &AddComponent<Sprite>("banana.png", 10);
}

StaticBackground::~StaticBackground()
{
	delete m_SpriteComponent;
}

void StaticBackground::Start() 
{

}