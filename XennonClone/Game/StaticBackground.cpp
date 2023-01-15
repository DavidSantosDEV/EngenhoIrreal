#include "StaticBackground.h"
#include "Sprite.h"
#include "GameEngine.h"

StaticBackground::StaticBackground() : GameObject() 
{
	m_SpriteComponent = AddComponent<Sprite>("galaxy2.bmp", -2);
}

void StaticBackground::Start()
{
	_Transform.SetPosition(0.f, m_SpriteComponent->GetSheetHeight());
}

StaticBackground::~StaticBackground()
{
	delete m_SpriteComponent;
}