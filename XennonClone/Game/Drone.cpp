#include "Drone.h"
#include "PhysicsComponent.h"
#include <math.h> 
#include "Log.h"
#include "GameWorld.h"

Drone::Drone()
{
	AddTag("Drone");
	m_SineMovementData = SineMovementData(3.f, 1.f);
	m_EnemyData = EnemyData("Enemy", "png/drone.png", 8, 2, 1.f, 25, 10, 25, 35);
	Setup();
}

void Drone::Update(float deltaTime)
{
	// Get a configurable value that is always increasing 
	m_SineMovementData.ticksCounter += m_SineMovementData.sineSpeed * deltaTime;
	// Get the sin for that value (will continuously return between -1 and 1)
	m_MoveDirection.x = m_SineMovementData.sineAmplitude * sin(m_SineMovementData.ticksCounter);
	m_PhysicsComponent->SetVelocity(m_MoveDirection * m_EnemyData.speed);
}

void Drone::OnBecameVisible()
{
	bCanDestroy = true;
}

void Drone::OnBecameHidden()
{
	if (bCanDestroy) {
		GameWorld::DestroyObject(this);
	}

}
