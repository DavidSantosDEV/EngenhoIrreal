#pragma once
#include "Pawn.h"

class PhysicsComponent;
class CircleCollision;
class HealthComponent;

class Player : public Pawn
{
public:
	Player();
	virtual void Update(float deltaTime) override;
	virtual void HandleEvents() override;
	virtual void OnZeroHealth() override;

	virtual void OnBecameVisible() override;
	virtual void OnBecameHidden() override;

	bool GetIsShooting() { return m_isShooting; }

	void DoLog() {
		LOG("HEY")
	}
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

	bool m_isShooting=false;
	float m_FireRate = 0.2f;
	float m_ShotsTimer = 0.f;
	int m_MoveSpeed = 100;
	Vector2D m_FirePosition;
};

