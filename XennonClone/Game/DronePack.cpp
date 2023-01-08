#include "DronePack.h"
#include "GameWorld.h"
#include "Drone.h"
#include "PhysicsComponent.h"
#include "EnemyManager.h"

void DronePack::Update(float deltaTime)
{
	if (m_NumberDronesToSpawn <= 0) { 
		GameWorld::DestroyObject(this);
		return;
	}
	m_SpawnsTimer += deltaTime;
	if (m_SpawnsTimer >= m_TimeBetweenSpawns)
	{
		// 35 is a miscellaneous number which represents the space between each drone
		Vector2D difference = Vector2D(0, m_NumberDronesToSpawn * 50);
		Drone* d = GameWorld::InstantiateObject<Drone>();
		d->GetComponent<PhysicsComponent>()->SetPosition(_Transform.GetPosition() - difference);
		//EnemyManager::GetInstance()->AddEnemy(d);
		m_NumberDronesToSpawn--;
		m_SpawnsTimer = 0;
	}
}
