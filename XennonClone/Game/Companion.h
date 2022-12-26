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


protected:

	float m_ShootDelay= 0.2f;
	void Shoot();

public:

	Delegate<Companion*> OnCompanionDie;

	Companion(Vector2D position);
	
	void SetTarget(Player* newTarget, Vector2D localPosition);
	virtual void Update(float delta) override;
	void OnZeroHealth();


	virtual void UpgradeShields(int amountToHeal) { LOG_ERROR(" Forgot to override IUpgradableShip methods") };
	virtual void UpgradeWeaponPower() { LOG_ERROR(" Forgot to override IUpgradableShip methods") };
	virtual void AddCompanion() {};

	Vector2D GetPositionTarget() { return m_playerOffSet; }
};

