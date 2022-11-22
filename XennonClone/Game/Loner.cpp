#include "Loner.h"
#include "PhysicsComponent.h"
#include "GameWorld.h"
#include "HomingMissile.h"

void Loner::Shoot()
{
	GameWorld::InstantiateObject<HomingMissile>()->GetPhysicsComponent()->
		SetPosition(m_Transform.GetPosition());
}

Loner::Loner()
{
	m_EnemyData = EnemyData("Enemy", "lonerA.bmp", 4, 4, 1.f, 35, 10, 10, 10);
	Setup();
	currentDelay = shootDelay;
	AddTag("Loner");
}

void Loner::Update(float deltaTime)
{

	m_PhysicsComponent->SetVelocity(m_MoveDirection * m_EnemyData.speed);

	currentDelay -= deltaTime;
	if (currentDelay<=0) {
		Shoot();
		currentDelay = shootDelay;
	}
}
