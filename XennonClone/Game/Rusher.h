#pragma once
#include "Enemy.h"

class Rusher : public Enemy
{
public:
	Rusher();

	Vector2D m_MoveDirection = Vector2D::Down();

	virtual void Update(float deltaTime) override;
};

