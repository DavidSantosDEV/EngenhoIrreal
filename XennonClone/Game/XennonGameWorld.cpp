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
#include "StoneAsteroid.h"

void XennonGameWorld::Start()
{
	InstantiateObject<EnemyManager>();
	StaticBackground* background = InstantiateObject<StaticBackground>();
	InstantiateObject<RocksBackground>();

	m_player = InstantiateObject<Player>();
	
	m_player->GetComponent<PhysicsComponent>()->SetPosition(m_PlayerStartPos);
	m_player->GetComponent<HealthComponent>()->OnDie.Add(this, &XennonGameWorld::OnPlayerDie);

	InstantiateObject<DronePack>()->_Transform.SetPosition(Vector2D(300, -300));
	InstantiateObject<MetalAsteroid>()->GetComponent<PhysicsComponent>()->SetPosition(Vector2D(50, -50));
	m_currentPlayerLifeCount = m_MaxPlayerLifeCount;

	//TimerManager::CreateTimer(this, &XennonGameWorld::RespawnPlayer, 5,false, true);
	//InstantiateObject<MetalAsteroid>()->GetComponent<PhysicsComponent>()->SetPosition(Vector2D(50, -50));
	InstantiateObject<StoneAsteroid>()->GetComponent<PhysicsComponent>()->SetPosition(Vector2D(300, -50));
	//InstantiateObject<Rusher>()->GetComponent<PhysicsComponent>()->SetPosition(Vector2D(300, -300));
	//InstantiateObject<Loner>()->GetComponent<PhysicsComponent>()->SetPosition(Vector2D(800, 300));
}

void XennonGameWorld::Update(float deltaTime)
{
}

void XennonGameWorld::RespawnPlayer()
{
	LOG_ERROR("TIMED");
}

void XennonGameWorld::OnPlayerDie()
{
	//Remove Lives
	m_currentPlayerLifeCount =MathHelper::ClampInt(m_currentPlayerLifeCount- 1,0,m_MaxPlayerLifeCount);
	if (m_currentPlayerLifeCount>0) {
		//Revive on input? or just revive
		
	}
	else {
		//He dead restart :)
		RespawnPlayer();
	}
}

void XennonGameWorld::AddScore(unsigned int value)
{
	m_currentScore += value;
	if (m_currentScore>m_BestScore) {
		m_BestScore = m_currentScore;
	}
}

void XennonGameWorld::ClearCurrent()
{
	m_currentScore = 0;
}
