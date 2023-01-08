#pragma once
#include "GameObject.h"


class PowerUpManager : public GameObject //Use to spawn Powerups
{
public:
	virtual void Update(float delta) override;
protected:
	Vector2D m_SpawnPositions[4] = { Vector2D(50,-10), Vector2D(300,-10.f), Vector2D(150,-10.f), Vector2D(200,-10.f) };
	float currentTime;
	float waitTime = 20.f;
	Vector2D GetRandomPosition();
	void SpawnRandomPickup();
};

