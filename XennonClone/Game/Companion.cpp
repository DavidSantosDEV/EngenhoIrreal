#include "Companion.h"
#include "Player.h"
#include "GameWorld.h"
#include "Sprite.h"
#include "PhysicsComponent.h"
#include "CircleCollision.h"
#include "AnimationComponent.h"
#include "HealthComponent.h"

void Companion::Shoot()
{

}

Companion::Companion(Vector2D position)
{
	GetTransform()->SetPosition(position);

	m_FollowTarget = nullptr;

	//const char* texturePath, int spriteSheetColumns, int spriteSheetRows, float scale, int renderPriority
	spriteComp = AddComponent<Sprite>("clone.bmp",4,4,1.f,1);
	animComp = AddComponent<AnimationComponent>(spriteComp,true,1.f);
	
	HealthComp = AddComponent<HealthComponent>(100);
	HealthComp->OnDie.Add(this, &Companion::OnZeroHealth);

	physComp = AddComponent<PhysicsComponent>(BodyType::Dynamic, 0, 1, 1);
	colComp = AddComponent<CircleCollision>(physComp, 10);
}

void Companion::SetTarget(Player* newTarget, Vector2D localPosition)
{
	if (newTarget) {
		m_FollowTarget = newTarget;
		m_playerOffSet = localPosition;
	}
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
	OnCompanionDie.Broadcast(this);
	GameWorld::DestroyObject(this);
}
