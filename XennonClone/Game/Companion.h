#pragma once

#include "GameObject.h"


class Companion : public GameObject
{

protected:

	class Player* m_FollowTarget;
	class Sprite* spriteComp;
	class AnimationComponent* animComp;
	class PhysicsComponent* physComp;
	class CircleCollision* colComp;



protected:

	float m_ShootDelay= 0.2f;
	void Shoot();

public:
	Companion();
	
	void SetTarget(Player* newTarget, Vector2D localPosition);
	virtual void Update(float delta) override;
	void OnZeroHealth();
};

