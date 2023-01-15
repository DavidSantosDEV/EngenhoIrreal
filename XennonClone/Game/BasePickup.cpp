#include "BasePickup.h"
#include "Sprite.h"
#include "AnimationComponent.h"
#include "PhysicsComponent.h"
#include "CircleCollision.h"
#include "IUpgradableShip.h"
#include "GameWorld.h"

BasePickup::BasePickup()
{
	AddTag("Pickup");
}

void BasePickup::SetupPickup(const char* spritePath, int spriteColumns, int spriteRows, int colliderRadius)
{
	m_SpriteComponent = AddComponent<Sprite>(spritePath, spriteColumns,
		spriteRows, 1.f, 1);
	m_AnimationComponent = AddComponent<AnimationComponent>(m_SpriteComponent, true, 8.f);
	m_PhysicsComponent = AddComponent<PhysicsComponent>(BodyType::Kinematic, 0, 1, 1);
	m_Collider = AddComponent<CircleCollision>(m_PhysicsComponent, colliderRadius);
	m_Collider->SetIsTrigger(true);
	m_Collider->OnTriggerEnter.Add(this, &BasePickup::OnTriggerEnter);
}

void BasePickup::Update(float deltaTime)
{
	m_PhysicsComponent->SetVelocity(Vector2D::Down() * 30.f);
}

void BasePickup::OnTriggerEnter(GameObject* other)
{
	IUpgradableShip* otherUpgradableShip = dynamic_cast<IUpgradableShip*>(other);
	if (otherUpgradableShip != nullptr)
	{
		CallPickupPower(otherUpgradableShip);
	}
	GameWorld::DestroyObject(this);
}

void BasePickup::OnBecameHidden()
{
	if (bWasVisible) {
		GameWorld::DestroyObject(this);
	}
}

void BasePickup::OnBecameVisible()
{
	bWasVisible = true;
}
