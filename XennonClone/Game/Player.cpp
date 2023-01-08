#include "Player.h"
#include "Input.h"
#include "Sprite.h"
#include "AnimationComponent.h"
#include "GameWorld.h"
#include "PhysicsComponent.h"
#include "CircleCollision.h"
#include "PlayerBullet.h"
#include "HealthComponent.h"
#include "Explosion.h"
#include "TimerManager.h"
#include "MathHelper.h"
#include "GameEngine.h"

Player::Player()
{
	AddTag("Player");

	m_SpriteComponent = AddComponent<Sprite>("Ship1.bmp", 7, 1, 1.f, 1);
	m_AnimationComponent = AddComponent<AnimationComponent>(m_SpriteComponent, false, 8.f);

	m_PhysicsComponent = AddComponent<PhysicsComponent>(BodyType::Dynamic, 0, 1, 1);
	m_Collider = AddComponent<CircleCollision>(m_PhysicsComponent, 20);
	m_HealthComponent = AddComponent<HealthComponent>(100);
	m_HealthComponent->OnDie.Add(this, &Player::OnZeroHealth);
}

void Player::HandleEvents()
{
	Pawn::HandleEvents();
	m_isShooting = Input::IsFireKeyDown();
	if (m_isShooting && m_ShotsTimer >= m_FireRate)
	{
		int bulletPositionMultiplier = 1;
		for (unsigned int i = 0; i < m_WeaponLevel; ++i)
		{
			PlayerBullet* bullet = GameWorld::InstantiateObject<PlayerBullet>();
			// TODO don't get component every frame
			bullet->GetPhysicsComponent()->SetPosition(CalculateFirePosition(bulletPositionMultiplier));
			bulletPositionMultiplier *= -1;
		}
		m_ShotsTimer = 0.f;
	}
	if (Input::IsChangeRenderingKeyDown() && m_ShotsTimer >= m_FireRate)
	{
		GameEngine::s_IsUsingOpenGLRendering = !GameEngine::s_IsUsingOpenGLRendering;
		m_ShotsTimer = 0.f;
	}
}

void Player::OnZeroHealth()
{
	GameWorld::InstantiateObject<Explosion>()->_Transform.SetPosition(_Transform.GetPosition());
	GameWorld::DestroyObject(this);
}

void Player::OnBecameVisible()
{
	LOG("Visible");
}

void Player::OnBecameHidden()
{
	LOG("Hidden");
}

void Player::UpgradeShields(int amountToHeal)
{
	LOG_WARNING("Player Shields Upgraded");
	m_HealthComponent->Heal(amountToHeal);
}

void Player::UpgradeWeaponPower()
{
	LOG_WARNING("Player WeaponPower Upgraded");
	m_WeaponLevel = MathHelper::ClampInt(m_WeaponLevel + 1, 1, 2);
}

void Player::Update(float deltaTime)
{
	m_ShotsTimer += deltaTime;

	Move(deltaTime);
	ChangeAnimationBasedOnInput();

	Pawn::Update(deltaTime);
}

void Player::Move(float deltaTime)
{
	Vector2D movement = (Vector2D(m_InputRightAxis, -m_InputUpAxis));
	movement.Normalize();
	movement *= m_MoveSpeed;
	m_PhysicsComponent->SetVelocity(movement);
}

void Player::ChangeAnimationBasedOnInput()
{
	if (m_InputRightAxis > 0.f)
	{
		if (!m_AnimationComponent->IsPlayingAnimation(0, 4, 0, 6)) m_AnimationComponent->PlayAnimation(0, 4, 0, 6, false);
	}
	else if (m_InputRightAxis < 0.f)
	{
		if (!m_AnimationComponent->IsPlayingAnimation(0, 0, 0, 2)) m_AnimationComponent->PlayAnimation(0, 0, 0, 2, false);
	}
	else
	{
		if (!m_AnimationComponent->IsPlayingAnimation(0, 3, 0, 3)) m_AnimationComponent->PlayAnimation(0, 3, 0, 3, true);
	}
}

Vector2D& Player::CalculateFirePosition(int positionMultiplier)
{
	m_FirePosition = _Transform.GetPosition() + Vector2D(17.f * positionMultiplier, 0);
	return m_FirePosition;
}

