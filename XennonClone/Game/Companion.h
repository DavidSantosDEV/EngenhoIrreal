#pragma once

#include "GameObject.h"
#include "IUpgradableShip.h"
#include "Delegate.h"


class Companion : public GameObject, public IUpgradableShip
{

protected:

	class Player* m_FollowTarget;
	class Sprite* spriteComp;
	class AnimationComponent* animComp;
	class PhysicsComponent* physComp;
	class CircleCollision* colComp;
	class HealthComponent* HealthComp;

	Vector2D m_playerOffSet;
	Vector2D m_bulletPos;

	float m_FireRate = 0.2f;
	float m_ShotsTimer = 0.f;

	int weaponPower = 1;

public:

	Delegate<Companion*> OnCompanionDie;

	virtual void Start() override;

	Companion(Vector2D position);
	
	void SetTarget(Player* newTarget, Vector2D localPosition);
	virtual void Update(float delta) override;
	void OnZeroHealth();

	void OnPlayerDie();

	virtual void UpgradeShields(int amountToHeal) override;
	virtual void UpgradeWeaponPower() override; //Upgrade weapon
	virtual void AddCompanion() {};

	Vector2D GetPositionTarget() { return m_playerOffSet; }
};

