#include "Loner.h"
#include "PhysicsComponent.h"
#include "GameWorld.h"
#include "HomingMissile.h"

void Loner::Shoot()
{
	GameWorld::InstantiateObject<HomingMissile>()->GetPhysicsComponent()->
		SetPosition(_Transform.GetPosition());
}

Loner::Loner()
{
	m_EnemyData = EnemyData("Enemy", "png/lonerA.png", 4, 4, 1.f, 35, 10, 50, 10);
	Setup();
	currentDelay = shootDelay;
	AddTag("Loner");
}

void Loner::Update(float deltaTime)
{
	m_PhysicsComponent->SetVelocity(m_MoveDirection * m_EnemyData.speed);

	if (canShoot) {
		currentDelay -= deltaTime;
		if (currentDelay <= 0) {
			Shoot();
			currentDelay = shootDelay;
		}
	}

}

void Loner::OnBecameVisible()
{
	canShoot = true;
}

void Loner::OnBecameHidden()
{
	if (canShoot) {
		Enemy::OnBecameHidden();
	}
}
