#include "Enemy.h"
#include "PhysicsComponent.h"
#include "CircleCollision.h"
#include "HealthComponent.h"
#include "Sprite.h"
#include "AnimationComponent.h"
#include "TextPopup.h"
//#include "GameWorld.h"
#include "EnemyManager.h"
#include "Explosion.h"
#include <cmath>
#include "Log.h"
#include "XennonGameWorld.h"

void Enemy::Setup() 
{
	AddTag(m_EnemyData.tag);

	m_SpriteComponent = AddComponent<Sprite>(m_EnemyData.texturePath, m_EnemyData.spriteColumns, 
		m_EnemyData.spriteRows, m_EnemyData.scale, 1);
	m_AnimationComponent = AddComponent<AnimationComponent>(m_SpriteComponent, true, 8.f);
	m_PhysicsComponent = AddComponent<PhysicsComponent>(BodyType::Kinematic, 0, 1, 1);
	m_Collider = AddComponent<CircleCollision>(m_PhysicsComponent, m_EnemyData.colliderRadius);

	m_HealthComponent = AddComponent<HealthComponent>(m_EnemyData.maxHealth);
	m_HealthComponent->OnDie.Add(this, &Enemy::OnZeroHealth);
	m_Collider->SetIsTrigger(true);
	m_Collider->OnTriggerEnter.Add(this, &Enemy::OnTriggerEnter);
}

void Enemy::TestFunc(int v, int b)
{
 	LOG_ERROR("Enemy Killed" << v << "d "<< b);
}

void Enemy::OnDestroyed()
{
	if (EnemyManager::GetInstance() != nullptr) {
		EnemyManager::GetInstance()->DeleteEnemy(this);
	}
}

void Enemy::OnZeroHealth()
{
	GameWorld::InstantiateObject<Explosion>()->GetTransform()->SetPosition(_Transform.GetPosition());

	XennonGameWorld* world = dynamic_cast<XennonGameWorld*>(GameWorld::GetWorld());
	if (world) {

		world->AddScore(score);
		//std::string text, float time, Vector2D pos
		GameWorld::InstantiateObject<TextPopup>(std::to_string(score),2.f,_Transform.GetPosition());
	}

	GameWorld::DestroyObject(this);
}

void Enemy::OnTriggerEnter(GameObject* other)
{
	if (other->HasTag("Player"))
	{
		HealthComponent* playerHealthComp = other->GetComponent<HealthComponent>();
		if (playerHealthComp) {
			playerHealthComp->TakeDamage(m_EnemyData.enemyDamage);
		}
		// TODO place damage in player class
		m_HealthComponent->TakeDamage(20);
	}
}

void Enemy::OnBecameHidden()
{
	if (EnemyManager::GetInstance() != nullptr) {
		EnemyManager::GetInstance()->DeleteEnemy(this);
	}
}
