#include "Rusher.h"
#include "PhysicsComponent.h"

Rusher::Rusher()
{
	m_EnemyData = EnemyData("Enemy", "rusher.bmp", 4, 6, 1.f, 30, 10, 10, 40);
	Setup();
}

void Rusher::Update(float deltaTime)
{
	m_PhysicsComponent->SetVelocity(m_MoveDirection * m_EnemyData.speed);
}
