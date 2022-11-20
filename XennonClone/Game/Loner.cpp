#include "Loner.h"
#include "PhysicsComponent.h"


Loner::Loner()
{
	m_EnemyData = EnemyData("Enemy", "lonerA.bmp", 4, 4, 1.f, 35, 10, 10, 50);
	Setup();
}

void Loner::Update(float deltaTime)
{
	m_PhysicsComponent->SetVelocity(m_MoveDirection * m_EnemyData.speed);
}
