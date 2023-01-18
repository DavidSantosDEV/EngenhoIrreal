#include "XennonGameWorld.h"
#include "GameObject.h"
#include "Sprite.h"
#include "StaticBackground.h"
#include "Pawn.h"
#include "Log.h"
#include "AnimationComponent.h"
#include "Player.h"
#include "DronePack.h"
#include "Rusher.h"
#include "PhysicsComponent.h"
#include "EnemyManager.h"
#include "RocksBackground.h"
#include "Loner.h"
#include "MetalAsteroid.h"
#include "HealthComponent.h"
#include "TimerManager.h"
#include "MathHelper.h"
#include "CompanionPickup.h"
#include "StoneAsteroid.h"
#include "Companion.h"
#include "PowerUpManager.h"
#include "PlayerUI.h"

void XennonGameWorld::Start()
{
	InstantiateObject<EnemyManager>();

	InstantiateObject<PowerUpManager>();

	InstantiateObject<StaticBackground>();
	InstantiateObject<RocksBackground>();

	m_player = InstantiateObject<Player>();
	m_UIPlayer = InstantiateObject<PlayerUI>();
	m_UIPlayer->SetHighScore(0);
	
	m_player->GetComponent<PhysicsComponent>()->SetPosition(m_PlayerStartPos);
	m_player->GetComponent<HealthComponent>()->OnDie.Add(this, &XennonGameWorld::OnPlayerDie);

	DronePack* d = InstantiateObject<DronePack>();
	d->_Transform.SetPosition(Vector2D(300, -300));
	d->AddTag("GMWRld");
	InstantiateObject<MetalAsteroid>()->GetComponent<PhysicsComponent>()->SetPosition(Vector2D(50, -50));
	m_currentPlayerLifeCount = m_MaxPlayerLifeCount;
	//InstantiateObject<MetalAsteroid>()->GetComponent<PhysicsComponent>()->SetPosition(Vector2D(50, -50));
	//TimerManager::CreateTimer(this, &XennonGameWorld::RespawnPlayer, 5,false, true);
	//InstantiateObject<MetalAsteroid>()->GetComponent<PhysicsComponent>()->SetPosition(Vector2D(50, -50));
	//InstantiateObject<StoneAsteroid>()->GetComponent<PhysicsComponent>()->SetPosition(Vector2D(300, -50));
	//InstantiateObject<Rusher>()->GetComponent<PhysicsComponent>()->SetPosition(Vector2D(300, -300));
	//InstantiateObject<Loner>()->GetComponent<PhysicsComponent>()->SetPosition(Vector2D(800, 300));
}

void XennonGameWorld::Update(float delta)
{
	if (bPlayerDead) {
		currentWaitTime += delta;
		if (currentWaitTime>= playerRespawnTime) {
			RespawnPlayer();
			currentWaitTime = 0;
		}
	}
}

void XennonGameWorld::RespawnPlayer()
{
	m_player->GetComponent<HealthComponent>()->Revive();
	bPlayerDead = false;
	LOG_ERROR("TIMED");
}

void XennonGameWorld::OnPlayerDie()
{
	//Remove Lives
	m_currentPlayerLifeCount = MathHelper::ClampInt(m_currentPlayerLifeCount- 1,0,m_MaxPlayerLifeCount);
	LOG("Player Live cout " << m_currentPlayerLifeCount);
	bPlayerDead = true;
	if (!m_currentPlayerLifeCount>0) {
		ClearCurrent();
	}
	//TimerManager::CreateTimer(this, &XennonGameWorld::RespawnPlayer, 5, false, true);
}

void XennonGameWorld::AddScore(unsigned int value)
{
	m_currentScore += value;
	m_UIPlayer->SetCurrentScore(m_currentScore);
	if (m_currentScore>m_BestScore) {
		m_BestScore = m_currentScore;
		m_UIPlayer->SetHighScore(m_BestScore);
	}
	LOG("Current Score!: " << m_currentScore);
}

void XennonGameWorld::ClearCurrent()
{
	m_currentScore = 0;
	m_UIPlayer->SetCurrentScore(0);
	m_currentPlayerLifeCount = m_MaxPlayerLifeCount;
	LOG("Current Score: " << m_currentScore);
}
