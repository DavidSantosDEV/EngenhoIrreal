#pragma once
#include <iostream>
#include "GameObject.h"

class EnemyManager : public GameObject
{
protected:

	Vector2D RusherSpawns[4] = {Vector2D(50,-10), Vector2D(300,-10.f), Vector2D(150,-10.f), Vector2D(200,-10.f)};

	Vector2D LonerSpawns[3] = { Vector2D(800, 300),Vector2D(800, 50),Vector2D(800, 200) };

	float m_CurrentTime;

	float m_SpawnDelay = 3;

	int m_MaxEnemies=10;
	std::vector<class Enemy*> m_Enemies;

	static EnemyManager* m_Instance;
	int enemyCount = 0;

public:

	static EnemyManager* GetInstance() { return m_Instance; }

	virtual void Start() override;

	virtual void Update(float deltaTime) override;

	void SpawnEnemyAtRandom();

	void DeleteEnemy(class Enemy* enemy);
};

