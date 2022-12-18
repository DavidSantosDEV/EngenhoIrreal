#include "MetalAsteroid.h"
#include "PhysicsComponent.h"

MetalAsteroid::MetalAsteroid()
{
	// Random
	srand(time(NULL));
	int metalAsteroidType = rand() % 3;

	switch (metalAsteroidType)
	{
	case 0:
		m_EnemyData = EnemyData("Enemy", "MAster32.bmp", 8, 2, 1.f, 15, 999, 15, 30);
		break;
	case 1:
		m_EnemyData = EnemyData("Enemy", "MAster64.bmp", 8, 3, 1.f, 25, 999, 30, 30);
		break;
	case 2:
		m_EnemyData = EnemyData("Enemy", "MAster96.bmp", 5, 5, 1.f, 60, 999, 40, 30);
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

