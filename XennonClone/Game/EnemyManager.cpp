#include "EnemyManager.h"
#include "PhysicsComponent.h"
#include "GameWorld.h"
#include "Enemy.h"
#include "Loner.h"
#include "Rusher.h"
#include "Random"
#include "TimerManager.h"

EnemyManager* EnemyManager::m_Instance = nullptr;

void EnemyManager::Start()
{
	if (m_Instance != nullptr) {
		delete this;
		return;
	}
	m_Instance = this;
	m_CurrentTime = m_SpawnDelay;

	TimerManager::CreateTimer(this, &EnemyManager::SpawnEnemyAtRandom, m_SpawnDelay, true, true);
	//SpawnEnemyAtRandom();
}

void EnemyManager::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	/*
	m_CurrentTime -= deltaTime;
	if (m_CurrentTime<=0) {
		m_CurrentTime = m_SpawnDelay;
		SpawnEnemyAtRandom();
	}
	*/
}

void EnemyManager::SpawnEnemyAtRandom()
{	
	// TODO FIX. Enemy base class doesn't do anything, only child classes
	// Como resolver: o enemy manager tem de saber das classes de inimigos que existem no jogo
	// e escolhe random dentro dessas para fazer spawn


  	if (enemyCount< m_MaxEnemies) {
		Enemy* enemy = nullptr;
		Vector2D spawnPoint;
		if ((rand() % 100) > 50) {
			enemy = GameWorld::InstantiateObject<Loner>();
			spawnPoint = LonerSpawns[rand() % 3];
		}
		else {
			enemy = GameWorld::InstantiateObject<Rusher>();
			spawnPoint = RusherSpawns[rand() % 4];
		}
		if (enemy) {
			enemyCount++;
			enemy->GetComponent<PhysicsComponent>()->SetPosition(spawnPoint);
			m_Enemies.push_back(enemy);
			LOG_ERROR("Enemy Count: " << enemyCount);
		}

	}

}

void EnemyManager::DeleteEnemy(Enemy* enemy)
{
	if (!enemy)return;
	for (int i = 0; i < m_Enemies.size(); ++i)
	{
		if (m_Enemies[i] == enemy)
		{
			enemyCount--;
			//GameWorld::DestroyObject(enemy);
			m_Enemies.erase(m_Enemies.begin() + i);
			LOG_ERROR("Enemy Count: " << enemyCount);
			return;
		}
	}
}
