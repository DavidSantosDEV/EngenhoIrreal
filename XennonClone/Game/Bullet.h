#pragma once
#include "GameObject.h"

struct BulletData
{
	const char* texturePath = "";
	int rows = 1;
	int columns = 1;
	int damage = 20;
	const char* destroyTagCheck = "";
	int radius = 10;
	float scale = 1.f;
	int speed = 600;
	Vector2D moveDirection = Vector2D::Up();

	BulletData() {};

	BulletData(const char* spritePath, int spriteRows, int spriteColumns, int bulletDamage,
		const char* destroyTag, int rad, float sc, int moveSpeed, const Vector2D& directionToMove)
	{
		texturePath = spritePath;
		rows = spriteRows;
		columns = spriteColumns; 
		damage = bulletDamage;
		destroyTagCheck = destroyTag;
		radius = rad;
		scale = sc;
		speed = moveSpeed;
		moveDirection = directionToMove;
	}
};


class Bullet : public GameObject
{
public:
	Bullet() {};

	virtual void Update(float deltaTime) override;
	virtual void OnTriggerEnter(GameObject* other);
	virtual void OnBecameHidden() override;
	class PhysicsComponent* GetPhysicsComponent() const { return m_PhysicsComponent; }

protected:

	void Setup();

	BulletData m_BulletData;

	class AnimationComponent* m_AnimationComponent;
	class PhysicsComponent* m_PhysicsComponent = nullptr;
};

