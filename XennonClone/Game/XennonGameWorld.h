#pragma once
#include "GameWorld.h"

class XennonGameWorld : public GameWorld
{
protected:
	unsigned int m_currentScore = 0;
	unsigned int m_BestScore = 0;

	unsigned short m_MaxPlayerLifeCount = 3;
	unsigned short m_currentPlayerLifeCount = 0;

	class Player* m_player;

protected:
	// Inherited via GameWorld
	virtual void Start() override;

	virtual void Update(float deltaTime) override;

	void RespawnPlayer();

	void OnPlayerDie();

public:
	void AddScore(unsigned int value);

	void ClearCurrent();
	
	unsigned int GetBestScore() { return m_BestScore; }
	unsigned int GetCurrentScore() { return m_BestScore; }

	
};

