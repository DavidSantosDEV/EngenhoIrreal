#include "Explosion.h"
#include "Sprite.h"
#include "AnimationComponent.h"
#include "GameWorld.h"

Explosion::Explosion()
{
	m_SpriteComponent = AddComponent<Sprite>("png/explode64.png", 5, 2, 1.f, 0);
	m_AnimationComponent = AddComponent<AnimationComponent>(m_SpriteComponent, true, 12.f);
	m_AnimationComponent->SetCanLoopAnimation(false);
	m_AnimationComponent->OnAnimationEnded.Add(this, &Explosion::OnAnimationEnd);
}

void Explosion::OnAnimationEnd()
{
	GameWorld::DestroyObject(this);
}


