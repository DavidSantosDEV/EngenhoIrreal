#pragma once
#include "GameObject.h"
class DronePack : public GameObject
{
public:
	virtual void Update(float deltaTime) override;

private:
	int m_NumberDronesToSpawn = 8;
	float m_TimeBetweenSpawns = 0.25f;
	float m_SpawnsTimer = m_TimeBetweenSpawns;
};

