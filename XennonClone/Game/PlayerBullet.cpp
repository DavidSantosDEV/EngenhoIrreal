#include "PlayerBullet.h"
#include "Sprite.h"
#include "PhysicsComponent.h"
#include "CircleCollision.h"
#include "GameWorld.h"
#include "AnimationComponent.h"

PlayerBullet::PlayerBullet()
{
	AddComponent<Sprite>("missile.bmp", 2, 4, 2.f, 0);
	m_AnimationComponent = AddComponent<AnimationComponent>(GetComponent<Sprite>(), false, 8.f);
	m_PhysicsComponent = AddComponent<PhysicsComponent>(BodyType::Dynamic, 0, 1, 1);
	AddComponent<CircleCollision>(GetComponent<PhysicsComponent>(), 10);
	GetComponent<CircleCollision>()->SetIsTrigger(true);
}

PlayerBullet::~PlayerBullet()
{
	/*
	delete m_AnimationComponent;
	delete GetComponent<Sprite>();
	delete GetComponent<CircleCollision>();
	delete GetComponent<PhysicsComponent>();*/
}

void PlayerBullet::Update(float deltaTime)
{
	GetComponent<PhysicsComponent>()->SetVelocity(Vector2D::Up() * m_MoveSpeed);

	// Sprite Animation
	if (!m_AnimationComponent->IsPlayingAnimation(0, 0, 0, 1)) m_AnimationComponent->PlayAnimation(0, 0, 0, 1, true);

	GameObject::Update(deltaTime);

	m_DestroyTimer += deltaTime;

	if (m_DestroyTimer >= m_AutoDestroyBulletAfter)
	{
		Destroy();
	}
}

void PlayerBullet::OnTriggerEnter(GameObject* other)
{
	if (other->HasTag("Enemy")) {
		LOG("Hit this guy");
		GameWorld::GetWorld()->DestroyObject(this);
	}
}

