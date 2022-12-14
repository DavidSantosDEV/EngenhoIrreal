#pragma once
#include "Pawn.h"
#include "IUpgradableShip.h"
#include "Delegate.h"

class PhysicsComponent;
class CircleCollision;
class HealthComponent;

class Player : public Pawn, public IUpgradableShip
{
public:
	Player();
	virtual void Update(float deltaTime) override;
	virtual void HandleEvents() override;

	void OnZeroHealth();
	void OnRevive();

	virtual void OnBecameVisible() override;
	virtual void OnBecameHidden() override;

	bool GetIsShooting() { return m_isShooting; }

	void DoLog() {
		LOG("HEY")
	}

	/* IUpgradableShip Interface declarations */
	virtual void UpgradeShields(int amountToHeal) override;
	virtual void UpgradeWeaponPower() override;
	virtual void AddCompanion() override;


private:

	void OnCompanionDie(class Companion* co);
	void Move(float deltaTime);
	void ChangeAnimationBasedOnInput();

	/* Called when player fires a bullet */
	Vector2D& CalculateFirePosition(int positionMultiplier);

	// Components
	class AnimationComponent* m_AnimationComponent;
	class Sprite* m_SpriteComponent;
	class HealthComponent* m_HealthComponent;

	PhysicsComponent* m_PhysicsComponent;
	CircleCollision* m_Collider;

	int bulletPositionMultiplier = 1;
	bool m_isShooting =false;
	float m_FireRate = 0.2f;
	float m_ShotsTimer = 0.f;
	int m_MoveSpeed = 100;
	/* Shoots x projectiles at a time */
	int m_WeaponLevel = 1;

	Vector2D m_FirePosition;
	//Companion
	std::vector<Vector2D> m_CompanionPositions {Vector2D(100,0)};
	std::vector<Vector2D> m_AvailablePositions;
};

