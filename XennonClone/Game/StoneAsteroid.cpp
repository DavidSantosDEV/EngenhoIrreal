#include "StoneAsteroid.h"
#include "PhysicsComponent.h"
#include "GameWorld.h"

StoneAsteroid::StoneAsteroid()
{
	srand(time(NULL));
	m_AsteroidType = (AsteroidType)(rand() % 3);
	SetupAsteroidData();
	
}

StoneAsteroid::StoneAsteroid(AsteroidType asteroidType)
{
	m_AsteroidType = asteroidType;
	SetupAsteroidData();
}


void StoneAsteroid::SetupAsteroidData()
{
	switch (m_AsteroidType)
	{
	case AsteroidType::Small:
		m_EnemyData = EnemyData("Enemy", "png/SAster32.png", 8, 2, 1.f, 15, 15, 15, 40);
		break;
	case AsteroidType::Medium:
		m_EnemyData = EnemyData("Enemy", "png/SAster64.png", 8, 3, 1.f, 25, 15, 30, 35);
		break;
	case AsteroidType::Large:
		m_EnemyData = EnemyData("Enemy", "png/SAster96.png", 5, 5, 1.f, 60, 30, 40, 25);
		break;
	default:
		LOG_ERROR("no valid stone asteroid type");
		break;
	}
	Setup();
}

void StoneAsteroid::Update(float deltaTime)
{
	m_PhysicsComponent->SetVelocity(m_MovementDirection * m_EnemyData.speed);
}

void StoneAsteroid::OnDestroyed()
{
	if (m_AsteroidType == AsteroidType::Large ||
		m_AsteroidType == AsteroidType::Medium)
	{
		/* When smaller asteroids are created, one will go 45º to the left and the other 45º to the right */
		float directionMultiplier = 0.5f;
		AsteroidType smallerAsteroidType = (AsteroidType)((int)m_AsteroidType - 1);
		for (int i = 0; i < 2; ++i)
		{
			StoneAsteroid* smallerAsteroid = GameWorld::InstantiateObject<StoneAsteroid>(smallerAsteroidType);
			smallerAsteroid->GetComponent<PhysicsComponent>()->SetPosition(_Transform.GetPosition());
			smallerAsteroid->m_MovementDirection = Vector2D(directionMultiplier, 0.5f);
			directionMultiplier *= -1;
		}
	}
	Enemy::OnDestroyed();
}
