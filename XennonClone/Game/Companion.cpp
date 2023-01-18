#include "Companion.h"
#include "Player.h"
#include "GameWorld.h"
#include "Sprite.h"
#include "PhysicsComponent.h"
#include "CircleCollision.h"
#include "AnimationComponent.h"
#include "HealthComponent.h"
#include "PlayerBullet.h"
#include "MediumBullet.h"
#include "HeavyBullet.h"
#include "MathHelper.h"
#include "Explosion.h"


void Companion::Start()
{
	animComp->PlayAnimation(0, 0, 3, 3, true);
	animComp->SetAnimationSpeed(3.f);
}

Companion::Companion(Vector2D position)
{
	AddTag("Player");

	GetTransform()->SetPosition(position);

	m_FollowTarget = nullptr;

	//const char* texturePath, int spriteSheetColumns, int spriteSheetRows, float scale, int renderPriority
	spriteComp = AddComponent<Sprite>("png/clone.png",4,5,1.f,1);
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
		m_FollowTarget->GetHealthComponent()->OnDie.Add(this, &Companion::OnPlayerDie);
		m_playerOffSet = localPosition;
	}
}

void Companion::Update(float delta)
{
	m_ShotsTimer += delta;
	if (m_FollowTarget) {
		if (m_FollowTarget->GetIsShooting() && m_ShotsTimer >= m_FireRate)
		{
			Bullet* bullet = nullptr;
			//Copy paste from player
			switch (weaponPower)
			{
			case 2:
				bullet = GameWorld::InstantiateObject<MediumBullet>();
				break;
			case 3:
				bullet = GameWorld::InstantiateObject<HeavyBullet>();
				break;
			default:
			case 1:
				bullet = GameWorld::InstantiateObject<PlayerBullet>();
				break;
			}
			if (bullet) {
				bullet->GetPhysicsComponent()->SetPosition(GetTransform()->GetPosition() + m_bulletPos);
				m_ShotsTimer = 0.f;
			}
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

void Companion::OnPlayerDie()
{
	GameWorld::DestroyObject(this);
}

void Companion::UpgradeShields(int amountToHeal)
{
	HealthComp->Heal(amountToHeal);
}

void Companion::UpgradeWeaponPower()
{
	weaponPower += 1;
	weaponPower = MathHelper::ClampInt(weaponPower, 1, 3);
}
