#pragma once
#include "GameObject.h"

struct EnemyData
{
	const char* tag = "";
	const char* texturePath = "";
	int spriteColumns = 1;
	int spriteRows = 1;
	float scale = 1.f;
	int colliderRadius = 20;
	int maxHealth = 10;
	int enemyDamage = 100;
	int speed = 70;

	EnemyData() {};

	EnemyData(const char* enemyTag, const char* path, int columns, int rows, float sc, int radius,
		int health, int damage, int spd)
	{
		tag = enemyTag;
		texturePath = path;
		spriteColumns = columns;
		spriteRows = rows;
		scale = sc;
		colliderRadius = radius;
		maxHealth = health;
		enemyDamage = damage;
		speed = spd;
	}
};

class Enemy : public GameObject
{
protected:

	/* Called in child classes to setup a generic enemy */
	void Setup();

	class Sprite* m_SpriteComponent = nullptr;
	class AnimationComponent* m_AnimationComponent = nullptr;
	class PhysicsComponent* m_PhysicsComponent = nullptr;
	class CircleCollision* m_Collider = nullptr;
	class HealthComponent* m_HealthComponent = nullptr;

	/* Edit on child classes to create different types of enemies*/
	EnemyData m_EnemyData;

public:
	Enemy() {};
	void TestFunc(int bal, int val);
	virtual void OnDestroyed() override;
	void OnZeroHealth();
	virtual void OnTriggerEnter(GameObject* other) override;
	virtual void OnBecameHidden() override;
};

