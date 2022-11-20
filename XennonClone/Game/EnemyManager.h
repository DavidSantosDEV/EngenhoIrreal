#pragma once
#include <iostream>
#include "GameObject.h"

class EnemyManager : public GameObject
{
protected:

	Vector2D VectorSpawns[5] = {Vector2D(50,0),Vector2D(0,0), Vector2D(300,0.f), Vector2D(150,0.f), Vector2D(200,0.f)};

	float currentTime;

	float m_SpawnDelay = 2;

	int m_MaxEnemies=10;
	std::vector<class Enemy*> enemies;

	static EnemyManager* m_Instance;

public:

	static EnemyManager* GetInstance() { return m_Instance; }

	virtual void Start() override;

	virtual void Update(float deltaTime) override;

	void SpawnEnemyAtRandom();

	void DeleteEnemy(Enemy* enemy);
};

