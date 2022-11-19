#include "Explosion.h"
#include "Sprite.h"
#include "AnimationComponent.h"
#include "GameWorld.h"

Explosion::Explosion()
{
	m_SpriteComponent = AddComponent<Sprite>("explode64.bmp", 5, 2, 1.f, 0);
	m_AnimationComponent = AddComponent<AnimationComponent>(m_SpriteComponent, true, 6.f);
	m_AnimationComponent->SetCanLoopAnimation(false);
}

void Explosion::OnAnimationEnd()
{
	GameWorld::DestroyObject(this);
}


