#include "DronePack.h"
#include "GameWorld.h"
#include "Drone.h"
#include "PhysicsComponent.h"

void DronePack::Update(float deltaTime)
{
	if (m_NumberDronesToSpawn == 0) { return; }

	m_SpawnsTimer += deltaTime;
	if (m_SpawnsTimer >= m_TimeBetweenSpawns)
	{
		// 35 is a miscellaneous number which represents the space between each drone
		Vector2D difference = Vector2D(0, m_NumberDronesToSpawn * 50);
		GameWorld::InstantiateObject<Drone>()->GetComponent<PhysicsComponent>()->
			SetPosition(_Transform.GetPosition() - difference);

		m_NumberDronesToSpawn--;
		m_SpawnsTimer = 0;
	}
}
