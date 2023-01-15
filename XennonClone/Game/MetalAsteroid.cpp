#include "MetalAsteroid.h"
#include "GameWorld.h"
#include "PhysicsComponent.h"

MetalAsteroid::MetalAsteroid()
{
	// Random
	srand(time(NULL));
	int metalAsteroidType = rand() % 3;

	switch (metalAsteroidType)
	{
	case 0:
		m_EnemyData = EnemyData("Enemy", "png/MAster32.png", 8, 2, 1.f, 15, 999, 15, 30);
		break;
	case 1:
		m_EnemyData = EnemyData("Enemy", "png/MAster64.png", 8, 3, 1.f, 25, 999, 30, 30);
		break;
	case 2:
		m_EnemyData = EnemyData("Enemy", "png/MAster96.png", 5, 5, 1.f, 60, 999, 40, 30);
		break;
	default:
		LOG_ERROR(metalAsteroidType << " " << "is not a valid metal asteroid type");
		break;
	}
	Setup();
}

void MetalAsteroid::Update(float deltaTime)
{
	m_PhysicsComponent->SetVelocity(m_MovementDirection * m_EnemyData.speed);
}

void MetalAsteroid::OnBecameHidden()
{
	GameWorld::DestroyObject(this);
}

