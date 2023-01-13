#pragma once
#include "GameWorld.h"
#include "Transform.h"

class XennonGameWorld : public GameWorld
{
protected:
	unsigned int m_currentScore = 0;
	unsigned int m_BestScore = 0;

	float playerRespawnTime = 5.f;
	float currentWaitTime = 0;

	unsigned short m_MaxPlayerLifeCount = 3;
	unsigned short m_currentPlayerLifeCount = 0;
	Vector2D m_PlayerStartPos = Vector2D(250, 300);
	class Player* m_player;

	bool bPlayerDead = false;

protected:
	// Inherited via GameWorld
	virtual void Start() override;
	virtual void Update(float delta) override;

	void RespawnPlayer();
	void OnPlayerDie();

public:
	void AddScore(unsigned int value);
	void ClearCurrent();
	unsigned int GetBestScore() { return m_BestScore; }
	unsigned int GetCurrentScore() { return m_BestScore; }
	unsigned short GetCurrentPlayerLifeCount() { return m_currentPlayerLifeCount; }
};

