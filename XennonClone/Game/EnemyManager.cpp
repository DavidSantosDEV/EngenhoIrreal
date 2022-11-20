#include "EnemyManager.h"
#include "PhysicsComponent.h"
#include "GameWorld.h"
#include "Enemy.h"
#include "Random"

EnemyManager* EnemyManager::m_Instance = nullptr;

void EnemyManager::Start()
{
	if (m_Instance) {
		delete this;
		return;
	}
	m_Instance = this;
	currentTime = m_SpawnDelay;
	SpawnEnemyAtRandom();
}

void EnemyManager::Update(float deltaTime)
{
	GameObject::Update(deltaTime);


	currentTime -= deltaTime;
	if (currentTime<=0) {
		currentTime = m_SpawnDelay;
		//SpawnEnemyAtRandom();
	}
}

void EnemyManager::SpawnEnemyAtRandom()
{	
  	if (enemies.size()< m_MaxEnemies) {
		
		Enemy* enemy = GameWorld::InstantiateObject<Enemy>();
		enemy->GetComponent<PhysicsComponent>()->SetPosition(VectorSpawns[rand() % 5]);
		enemies.push_back(enemy);
	}

}

void EnemyManager::DeleteEnemy(Enemy* enemy)
{
	if (!enemy)return;
	for (int i = 0; i < enemies.size(); ++i)
	{
		if (enemies[i] == enemy)
		{
			enemies.erase(enemies.begin() + i);
			return;
		}
	}
}
