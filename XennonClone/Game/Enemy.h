#pragma once
#include "GameObject.h"
class Enemy : public GameObject
{
protected:

	void Setup();

	class Sprite* m_SpriteComponent;
	class AnimationComponent* m_AnimationComponent;
	class PhysicsComponent* m_PhysicsComponent;
	class CircleCollision* m_Collider;
	class HealthComponent* m_HealthComponent;

	float enemySpeed = 60;


	float additor = 0;
	bool bDecreasing = false;
	float variation = 10;
	float sidewaySpeed = 30;

	Vector2D DesiredPosition;
	float AcceptedDistance = 2.f;

public:

	Enemy();

	virtual void Start() override;
	virtual void Update(float deltaTime) override;

	virtual void Destroy() override;

	virtual void OnZeroHealth() override;

	virtual void OnBeginCollision(GameObject* other) override;
};

