#pragma once
#include "Enemy.h"
class Loner : public Enemy
{
protected:
	float currentDelay;
	float shootDelay = 1.f;

	void Shoot();
public:
	Loner();

	Vector2D m_MoveDirection = Vector2D::Left();

	virtual void Update(float deltaTime) override;
};

