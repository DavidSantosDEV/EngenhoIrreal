#include "Bullet.h"
#include "Sprite.h"
#include "PhysicsComponent.h"
#include "CircleCollision.h"
#include "HealthComponent.h"
#include "GameWorld.h"
#include "AnimationComponent.h"
#include "Enemy.h"
#include "Explosion.h"

void Bullet::Setup()
{
	AddComponent<Sprite>(m_BulletData.texturePath, m_BulletData.columns, m_BulletData.rows, 
		m_BulletData.scale, 0);
	m_AnimationComponent = AddComponent<AnimationComponent>(GetComponent<Sprite>(), false, 8.f);
	m_PhysicsComponent = AddComponent<PhysicsComponent>(BodyType::Dynamic, 0, 1, 1);
	CollisionComponent* comp = AddComponent<CircleCollision>(GetComponent<PhysicsComponent>(), m_BulletData.radius);
	comp->SetIsTrigger(true);
	comp->OnTriggerEnter.Add(this, &Bullet::OnTriggerEnter);

	GetComponent<Sprite>()->SetIsVisible(true);
}


void Bullet::Update(float deltaTime)
{
	GetComponent<PhysicsComponent>()->SetVelocity(m_BulletData.moveDirection * m_BulletData.speed);
	GameObject::Update(deltaTime);
}

void Bullet::OnTriggerEnter(GameObject* other)
{
	if (other->HasTag(m_BulletData.destroyTagCheck))
	{
		HealthComponent* otherHealthComp = other->GetComponent<HealthComponent>();
		int otherHealthLeft = 0;
		if (otherHealthComp) {
			otherHealthLeft = otherHealthComp->TakeDamage(m_BulletData.damage);
		}

		// Only spawn explosion if other GO will not be destroyed (avoids overlapping expliosions)
		if (otherHealthLeft > 0)
		{
			GameWorld::InstantiateObject<Explosion>()->_Transform.SetPosition(_Transform.GetPosition());
		}

		GameWorld::DestroyObject(this);
	}
}

void Bullet::OnBecameHidden()
{
	GameWorld::DestroyObject(this);
}

