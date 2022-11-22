#pragma once
#include "Enemy.h"
class Loner : public Enemy
{
protected:

	bool canShoot=false;

	float currentDelay;
	float shootDelay = 2.f;

	void Shoot();
public:
	Loner();

	Vector2D m_MoveDirection = Vector2D::Left();

	virtual void Update(float deltaTime) override;

	virtual void OnBecameVisible() override;
};

