#include "Companion.h"
#include "Player.h"
#include "GameWorld.h"
#include "Sprite.h"
#include "PhysicsComponent.h"
#include "CircleCollision.h"
#include "AnimationComponent.h"
#include "HealthComponent.h"
#include "PlayerBullet.h"
#include "Explosion.h"


Companion::Companion(Vector2D position)
{
	AddTag("Player");

	GetTransform()->SetPosition(position);

	m_FollowTarget = nullptr;

	//const char* texturePath, int spriteSheetColumns, int spriteSheetRows, float scale, int renderPriority
	spriteComp = AddComponent<Sprite>("clone.bmp",4,4,1.f,1);
	animComp = AddComponent<AnimationComponent>(spriteComp,true,1.f);
	
	HealthComp = AddComponent<HealthComponent>(100);
	HealthComp->OnDie.Add(this, &Companion::OnZeroHealth);

	physComp = AddComponent<PhysicsComponent>(BodyType::Dynamic, 0, 1, 1);
	colComp = AddComponent<CircleCollision>(physComp, 10);
	m_bulletPos = Vector2D(3.f, 0);
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
	m_ShotsTimer += delta;
	if (m_FollowTarget) {
		if (m_FollowTarget->GetIsShooting() && m_ShotsTimer >= m_FireRate)
		{
			PlayerBullet* bullet = GameWorld::InstantiateObject<PlayerBullet>();
			// TODO don't get component every frame
			bullet->GetPhysicsComponent()->SetPosition(GetTransform()->GetPosition()+m_bulletPos);
			m_ShotsTimer = 0.f;
		}
		physComp->SetPosition(m_FollowTarget->GetTransform()->GetPosition() + m_playerOffSet);
	}
}

void Companion::OnZeroHealth()
{
	GameWorld::InstantiateObject<Explosion>(GetTransform());
	OnCompanionDie.Broadcast(this);
	GameWorld::DestroyObject(this);
}
