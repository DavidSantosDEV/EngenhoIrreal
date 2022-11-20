#include "EnemyManager.h"
#include "PhysicsComponent.h"
#include "GameWorld.h"
#include "Enemy.h"
#include "Random"

EnemyManager* EnemyManager::m_Instance = nullptr;

void EnemyManager::Start()
{
	if (m_Instance != nullptr) {
		delete this;
		return;
	}
	m_Instance = this;
	m_CurrentTime = m_SpawnDelay;
	//SpawnEnemyAtRandom();
}

void EnemyManager::Update(float deltaTime)
{
	GameObject::Update(deltaTime);


	m_CurrentTime -= deltaTime;
	if (m_CurrentTime<=0) {
		m_CurrentTime = m_SpawnDelay;
		//SpawnEnemyAtRandom();
	}
}

void EnemyManager::SpawnEnemyAtRandom()
{	
	// TODO FIX. Enemy base class doesn't do anything, only child classes
	// Como resolver: o enemy manager tem de saber das classes de inimigos que existem no jogo
	// e escolhe random dentro dessas para fazer spawn
  	if (m_Enemies.size()< m_MaxEnemies) {
		
		Enemy* enemy = GameWorld::InstantiateObject<Enemy>();
		enemy->GetComponent<PhysicsComponent>()->SetPosition(VectorSpawns[rand() % 5]);
		m_Enemies.push_back(enemy);
	}

}

void EnemyManager::DeleteEnemy(Enemy* enemy)
{
	if (!enemy)return;
	for (int i = 0; i < m_Enemies.size(); ++i)
	{
		if (m_Enemies[i] == enemy)
		{
			m_Enemies.erase(m_Enemies.begin() + i);
			return;
		}
	}
}
