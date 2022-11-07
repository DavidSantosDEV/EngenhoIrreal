#include "StaticBackground.h"
#include "Sprite.h"
#include "GameEngine.h"

StaticBackground::StaticBackground() : GameObject() 
{
	m_SpriteComponent = &AddComponent<Sprite>();
	m_SpriteComponent->SetSpriteTexture("banana.png");
	//m_SpriteComponent->SetSpriteScale(GameEngine::GetInstance()->GetWindowSize());
}

StaticBackground::~StaticBackground()
{
	delete m_SpriteComponent;
}

void StaticBackground::Start() 
{

}