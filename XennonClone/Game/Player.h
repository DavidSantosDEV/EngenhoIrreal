#pragma once
#include "Pawn.h"

class PhysicsComponent;
class CircleCollision;
class HealthComponent;

class Player : public Pawn
{
public:
	Player();
	~Player();
	virtual void Update(float deltaTime) override;
	virtual void HandleEvents() override;
	virtual void OnZeroHealth() override;

private:

	void Move(float deltaTime);
	void ChangeAnimationBasedOnInput();

	/* Called when player fires a bullet */
	Vector2D& CalculateFirePosition();

	// Components
	class AnimationComponent* m_AnimationComponent;
	class Sprite* m_SpriteComponent;
	class HealthComponent* m_HealthComponent;

	PhysicsComponent* m_PhysicsComponent;
	CircleCollision* m_Collider;


	float m_FireRate = 0.2f;
	float m_ShotsTimer = 0.f;
	int m_MoveSpeed = 100;
	Vector2D m_FirePosition;
};

