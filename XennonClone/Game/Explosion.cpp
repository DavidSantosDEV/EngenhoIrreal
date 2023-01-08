#include "Explosion.h"
#include "Sprite.h"
#include "AnimationComponent.h"
#include "GameWorld.h"

Explosion::Explosion()
{
	m_SpriteComponent = AddComponent<Sprite>("explode64.bmp", 5, 2, 1.f, 0);
	m_AnimationComponent = AddComponent<AnimationComponent>(m_SpriteComponent, true, 12.f);
	m_AnimationComponent->SetCanLoopAnimation(false);
	m_AnimationComponent->OnAnimationEnded.Add(this, &Explosion::OnAnimationEnd);
}

Explosion::Explosion(Transform* trnsfm)
{
	if(trnsfm) GetTransform()->SetPosition(trnsfm->GetPosition());
	m_SpriteComponent = AddComponent<Sprite>("explode64.bmp", 5, 2, 1.f, 0);
	m_AnimationComponent = AddComponent<AnimationComponent>(m_SpriteComponent, true, 12.f);
	m_AnimationComponent->SetCanLoopAnimation(false);
	m_AnimationComponent->OnAnimationEnded.Add(this, &Explosion::OnAnimationEnd);
}

void Explosion::OnAnimationEnd()
{
	GameWorld::DestroyObject(this);
}


