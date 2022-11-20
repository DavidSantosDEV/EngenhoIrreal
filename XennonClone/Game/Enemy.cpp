#include "Enemy.h"
#include "PhysicsComponent.h"
#include "CircleCollision.h"
#include "HealthComponent.h"
#include "Sprite.h"
#include "AnimationComponent.h"
#include "GameWorld.h"
#include "EnemyManager.h"
#include "Explosion.h"
#include <cmath>

Enemy::Enemy()
{
	Setup();
}


void Enemy::Setup() {

	AddTag("Enemy");

	m_SpriteComponent = AddComponent<Sprite>("drone.bmp", 8, 2, 1.f, 1);
	m_AnimationComponent = AddComponent<AnimationComponent>(m_SpriteComponent, false, 8.f);
	m_PhysicsComponent = AddComponent<PhysicsComponent>(BodyType::Dynamic, 0, 1, 1);
	m_Collider = AddComponent<CircleCollision>(m_PhysicsComponent, 20);
	m_HealthComponent = AddComponent<HealthComponent>(1);
}

void Enemy::Start()
{
	
}

void Enemy::Update(float deltaTime)
{
	Vector2D vel = Vector2D::Down();
	if (bDecreasing) {
		additor -= deltaTime*sidewaySpeed;
		if (additor<=-variation) {
			bDecreasing = false;
		}
	}
	else {
		additor += deltaTime*sidewaySpeed;
		if (additor>=variation) {
			bDecreasing = true;
		}
	}
	vel.x += additor;
	m_PhysicsComponent->SetVelocity(vel*enemySpeed);
}

void Enemy::Destroy()
{
 	EnemyManager::GetInstance()->DeleteEnemy(this);
}

void Enemy::OnZeroHealth()
{
	GameWorld::InstantiateObject<Explosion>()->GetTransform()->SetPosition(m_Transform.GetPosition());
	GameWorld::DestroyObject(this);
}

void Enemy::OnBeginCollision(GameObject* other)
{
	if (other->HasTag("Player")) {
		HealthComponent* h = other->GetComponent<HealthComponent>();
		if (h) {
			h->TakeDamage(10);
		}
		GameWorld::InstantiateObject<Explosion>()->GetTransform()->SetPosition(m_Transform.GetPosition());
		GameWorld::DestroyObject(this);
	}
}
