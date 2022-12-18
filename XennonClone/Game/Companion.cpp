#include "Companion.h"
#include "Player.h"
#include "GameWorld.h"
#include "Sprite.h"
#include "PhysicsComponent.h"
#include "CircleCollision.h"
#include "AnimationComponent.h"

void Companion::Shoot()
{

}

Companion::Companion()
{
	/*
	spriteComp = AddComponent<Sprite>();
	
	animComp = AddComponent<AnimationComponent>();
	physComp = AddComponent<PhysicsComponent>();

	colComp = AddComponent<CircleCollision>();*/

}

void Companion::SetTarget(Player* newTarget, Vector2D localPosition)
{

}

void Companion::Update(float delta)
{
	if (m_FollowTarget) {
		if (m_FollowTarget->GetIsShooting()) {

		}
	}
}

void Companion::OnZeroHealth()
{
	GameWorld::DestroyObject(this);
}
